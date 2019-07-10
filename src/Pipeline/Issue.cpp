//
// Created by Alex Chi on 2019-07-10.
//

#include <vector>

#include "Issue.h"
#include "OoOExecute.h"

#include "../Module/ALUUnit.h"
#include "../Session.h"

void Issue::update() {
    // Note that pc is register. No matter how
    // many times update is executed, pc always
    // stays the same.


    auto _inst = session->memory.read_word(pc);
    auto inst = parse_inst(_inst & 0x7f, _inst);

    pc = issue(inst);
}

void Issue::tick() {
    pc.tick();
}

ALUUnit::OP get_op_ri(InstructionBase inst) {
    switch (inst.funct3) {
        case 0b000:
            return ALUUnit::OP::ADD;
        case 0b010:
            return ALUUnit::OP::SLT;
        case 0b011:
            return ALUUnit::OP::SLTU;
        case 0b100:
            return ALUUnit::OP::XOR;
        case 0b110:
            return ALUUnit::OP::OR;
        case 0b111:
            return ALUUnit::OP::AND;
        case 0b001:
            return ALUUnit::OP::SLL;
        case 0b101:
            if (inst.imm & (1 << 9))
                return ALUUnit::OP::SRA;
            else
                return ALUUnit::OP::SRL;
    }
    assert(false);
    return ALUUnit::OP::NONE;
}

ALUUnit::OP get_op_rr(InstructionBase inst) {
    switch (inst.funct3) {
        case 0b000:
            if (inst.funct7 == 0b0000000) return ALUUnit::OP::ADD;
            if (inst.funct7 == 0b0100000) return ALUUnit::OP::SUB;
        case 0b001:
            return ALUUnit::OP::SLL;
        case 0b010:
            return ALUUnit::OP::SLT;
        case 0b011:
            return ALUUnit::OP::SLTU;
        case 0b100:
            return ALUUnit::OP::XOR;
        case 0b101:
            if (inst.funct7 == 0b0000000)
                return ALUUnit::OP::SRL;
            if (inst.funct7 == 0b0100000)
                return ALUUnit::OP::SRA;
        case 0b110: // OR
            return ALUUnit::OP::OR;
        case 0b111: // AND
            return ALUUnit::OP::AND;
    }
    assert(false);
    return ALUUnit::OP::NONE;
}

Immediate Issue::issue(const InstructionBase &inst) {
    if (inst.t == InstructionBase::J) {
        // JAL
        return pc + inst.imm;
    } else if (inst.t == InstructionBase::B) {
        // Branch
    } else if (inst.opcode == 0b0000011) { // Load
    } else if (inst.opcode == 0b0100011) { // Store
    } else if (inst.opcode == 0b0010011) { // Immediate Op
        auto op = get_op_ri(inst);
        auto unit_id = find_available_op_unit();
        if (unit_id == NONE) return pc;
        auto rs = session->e->get_rs(unit_id);
        rs->Op = op;
        rs->Qk = NONE;
        rs->Vk = inst.imm;
        if (session->e->should_rename_register(inst.rs1)) {
            rs->Vj = 0;
            rs->Qj = session->e->rename_register(inst.rs1, unit_id);
        } else {
            rs->Vj = session->rf.read(inst.rs1);
            rs->Qj = NONE;
        }
    } else if (inst.opcode == 0b0110011) { // Op
        auto op = get_op_rr(inst);
        auto unit_id = find_available_op_unit();
        if (unit_id == NONE) return pc;
        auto rs = session->e->get_rs(unit_id);
        rs->Op = op;
    }
    // LUI, AUIPC, JALR
    return pc + 4;
}

Issue::Issue(Session *session) : session(session) {}

InstructionBase Issue::parse_inst(unsigned opcode, Immediate inst) {
    if (opcode == 0b0110011) { return InstructionR(inst); } // ***
    if (opcode == 0b0010011) { return InstructionI(inst); } // ***I
    if (opcode == 0b0100011) { return InstructionS(inst); } // S*
    if (opcode == 0b0000011) { return InstructionI(inst); } // L*
    if (opcode == 0b1100011) { return InstructionB(inst); } // B**
    if (opcode == 0b1100111) { return InstructionI(inst); } // JALR
    if (opcode == 0b1101111) { return InstructionJ(inst); } // JAL
    if (opcode == 0b0010111) { return InstructionU(inst); } // AUIPC
    if (opcode == 0b0110111) { return InstructionU(inst); } // LUI
    return InstructionBase::nop();
}

void Issue::debug() {
    std::cout << "PC" << std::endl;
    std::cout << pc.current() << std::endl;
}

RSID Issue::find_available_op_unit() {
    static std::vector<RSID> op_unit = {ADD1, ADD2, ADD3};
    for (auto &&unit : op_unit) {
        if (session->e->available(unit)) return unit;
    }
    return NONE;
}
