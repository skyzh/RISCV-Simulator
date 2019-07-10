//
// Created by Alex Chi on 2019-07-10.
//

#include <vector>
#include <cassert>

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
    branch_issued.tick();
    issue_cnt.tick();
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
    return ALUUnit::OP::NONE_OP;
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
    return ALUUnit::OP::NONE_OP;
}

ALUUnit::OP get_op_branch(InstructionBase inst) {
    switch (inst.funct3) {
        case 0b000: // BEQ
        case 0b001: // BNE
            return ALUUnit::OP::SUB;
        case 0b100: // BLT
        case 0b101: // BGE
            return ALUUnit::OP::SLT;
        case 0b110: // BLTU
        case 0b111: // BGEU
            return ALUUnit::OP::SLTU;
    }
    assert(false);
    return ALUUnit::OP::NONE_OP;
}

Immediate Issue::issue(const InstructionBase &inst) {
    _debug_dispatched_inst = inst;
    issue_cnt = issue_cnt + 1;

    if (inst.t == InstructionBase::J) { // JAL
        return issue_jal(inst);
    } else if (inst.t == InstructionBase::B) { // Branch
        // TODO: branch should not cause hazard like
        //       this, we should apply speculation method
        // TODO: branch unit is the same as ALU Unit,
        //       we may randomly select one from them
        //       instead of specifying BRANCH1.
        if (branch_issued == false)
            return issue_branch(inst);
        // If branch has been resolved, we can issue next inst.
        if (session->e->available(BRANCH1))
            return resolve_branch(inst);
        // If branch is still being resolved, don't move to next inst.
        return pc;
    } else if (inst.opcode == 0b1100111) { // JALR
        if (branch_issued == false)
            return issue_jalr(inst);
        if (session->e->available(BRANCH1))
            return resolve_jalr(inst);
        return pc;
    } else if (inst.opcode == 0b0000011) { // Load
        return issue_load(inst);
    } else if (inst.opcode == 0b0100011) { // Store
        return issue_store(inst);
    } else if (inst.opcode == 0b0010011) { // Immediate Op
        return issue_immediate_op(inst);
    } else if (inst.opcode == 0b0110011) { // Op
        return issue_op(inst);
    } else if (inst.opcode == 0b0110111) { // LUI
        return issue_lui(inst);
    } else if (inst.opcode == 0b0110111) { // AUIPC
        return issue_auipc(inst);
    }
    return pc;
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
    std::cout << "PC prev->current" << std::endl;
    std::cout << std::hex << "\t" << pc << "\t" << pc.current() << std::endl;
    std::cout << "Instruction" << std::endl;
    _debug_dispatched_inst.debug();
    if (branch_issued.current()) std::cout << "(branch issued)" << std::endl;
}

RSID Issue::find_available_op_unit() {
    static const std::vector<RSID> op_unit = {ADD1, ADD2, ADD3};
    return find_available_unit_in(op_unit);
}

RSID Issue::find_available_load_unit() {
    static const std::vector<RSID> load_unit = {LOAD1};
    return find_available_unit_in(load_unit);
}

RSID Issue::find_available_store_unit() {
    static const std::vector<RSID> store_unit = {STORE1};
    return find_available_unit_in(store_unit);
}


Immediate Issue::issue_jalr(const InstructionBase &inst) {
    // TODO: here we use two unit to process jalr.
    //       first we obtain pc + 4 with alu unit,
    //       then we obtain next pc just as what
    //       issue does.
    if (!session->e->available(BRANCH1)) return pc;
    auto unit_id = find_available_op_unit();
    if (unit_id == NONE) return pc;

    {   // Branch
        auto rs = session->e->occupy_unit(BRANCH1);

        rs->Op = ALUUnit::OP::ADD;
        rs->Tag = issue_cnt;

        issue_rs_to_Vj(inst.rs1, rs, BRANCH1);
        issue_imm_to_Vk(inst.imm, rs, BRANCH1);

        session->e->rename_register(OoOExecute::BRANCH_REG, BRANCH1);
    }
    {   // Write back to rd
        auto rs = session->e->occupy_unit(unit_id);
        rs->Op = ALUUnit::OP::ADD;
        rs->Tag = issue_cnt;

        issue_imm_to_Vk(pc, rs, unit_id);
        issue_imm_to_Vj(4, rs, unit_id);

        session->e->rename_register(inst.rd, unit_id);
    }

    branch_issued = true;

    return pc;
}

Immediate Issue::resolve_jalr(const InstructionBase &inst) {
    branch_issued = false;
    return session->rf.read(OoOExecute::BRANCH_REG);
}

Immediate Issue::issue_branch(const InstructionBase &inst) {
    // If branch unit is not available, don't move to next inst.
    if (!session->e->available(BRANCH1)) return pc;
    auto rs = session->e->occupy_unit(BRANCH1);
    rs->Op = get_op_branch(inst);
    rs->Tag = issue_cnt;

    issue_rs_to_Vj(inst.rs1, rs, BRANCH1);
    issue_rs_to_Vk(inst.rs2, rs, BRANCH1);

    session->e->rename_register(OoOExecute::BRANCH_REG, BRANCH1);

    branch_issued = true;

    return pc;
}

Immediate Issue::issue_immediate_op(const InstructionBase &inst) {
    auto op = get_op_ri(inst);
    auto unit_id = find_available_op_unit();
    if (unit_id == NONE) return pc;

    auto rs = session->e->occupy_unit(unit_id);

    rs->Op = op;
    rs->Tag = issue_cnt;

    issue_rs_to_Vj(inst.rs1, rs, unit_id);
    issue_imm_to_Vk(inst.imm, rs, unit_id);

    session->e->rename_register(inst.rd, unit_id);

    return pc + 4;
}

Immediate Issue::issue_op(const InstructionBase &inst) {
    auto op = get_op_rr(inst);
    auto unit_id = find_available_op_unit();
    if (unit_id == NONE) return pc;

    auto rs = session->e->occupy_unit(unit_id);

    rs->Op = op;
    rs->Tag = issue_cnt;

    issue_rs_to_Vj(inst.rs1, rs, unit_id);
    issue_rs_to_Vk(inst.rs2, rs, unit_id);

    session->e->rename_register(inst.rd, unit_id);

    return pc + 4;
}

Immediate Issue::resolve_branch(const InstructionBase &inst) {
    branch_issued = false;
    auto branch_result = session->rf.read(OoOExecute::BRANCH_REG);
    auto branch_target = pc + inst.imm;
    auto next_inst = pc + 4;

    switch (inst.funct3) {
        case 0b000: // BEQ
            if (branch_result == 0) return branch_target;
            else return next_inst;
        case 0b001: // BNE
            if (branch_result != 0) return branch_target;
            else return next_inst;
        case 0b100: // BLT
            if (branch_result == 1) return branch_target;
            else return next_inst;
        case 0b101: // BGE
            if (branch_result == 0) return branch_target;
            else return next_inst;
        case 0b110: // BLTU
            if (branch_result == 1) return branch_target;
            else return next_inst;
        case 0b111: // BGEU
            if (branch_result == 0) return branch_target;
            else return next_inst;
    }

    assert(false);
    return pc;
}

void Issue::issue_rs_to_Vj(unsigned reg_id, RS *rs, RSID unit_id) {
    if (reg_id != 0 && session->e->should_rename_register(reg_id)) {
        rs->Vj = 0;
        rs->Qj = session->e->rename_register(reg_id, unit_id);
    } else {
        rs->Vj = session->rf.read(reg_id);
        rs->Qj = NONE;
    }
}

void Issue::issue_rs_to_Vk(unsigned reg_id, RS *rs, RSID unit_id) {
    if (reg_id != 0 && session->e->should_rename_register(reg_id)) {
        rs->Vk = 0;
        rs->Qk = session->e->rename_register(reg_id, unit_id);
    } else {
        rs->Vk = session->rf.read(reg_id);
        rs->Qk = NONE;
    }
}

void Issue::issue_imm_to_Vk(Immediate imm, RS *rs, RSID) {
    rs->Qk = NONE;
    rs->Vk = imm;
}

void Issue::issue_imm_to_Vj(Immediate imm, RS *rs, RSID) {
    rs->Qj = NONE;
    rs->Vj = imm;
}

Immediate Issue::issue_load(const InstructionBase &inst) {
    auto unit_id = find_available_load_unit();
    if (unit_id == NONE) return pc;

    auto rs = session->e->occupy_unit(unit_id);

    rs->Op = inst.funct3;
    rs->Tag = issue_cnt;

    issue_rs_to_Vj(inst.rs1, rs, unit_id);
    issue_imm_to_Vk(0, rs, unit_id);
    issue_imm_to_A(inst.imm, rs, unit_id);

    session->e->rename_register(inst.rd, unit_id);

    return pc + 4;
}

Immediate Issue::issue_store(const InstructionBase &inst) {
    auto unit_id = find_available_store_unit();
    if (unit_id == NONE) return pc;

    auto rs = session->e->occupy_unit(unit_id);

    rs->Op = inst.funct3;
    rs->Tag = issue_cnt;

    issue_rs_to_Vj(inst.rs1, rs, unit_id);
    issue_rs_to_Vk(inst.rs2, rs, unit_id);
    issue_imm_to_A(inst.imm, rs, unit_id);

    return pc + 4;
}

Immediate Issue::issue_lui(const InstructionBase &inst) {
    auto unit_id = find_available_op_unit();
    if (unit_id == NONE) return pc;

    auto rs = session->e->occupy_unit(unit_id);

    rs->Op = ALUUnit::OP::ADD;
    rs->Tag = issue_cnt;

    issue_imm_to_Vk(0, rs, unit_id);
    issue_imm_to_Vk(inst.imm, rs, unit_id);

    session->e->rename_register(inst.rd, unit_id);

    return pc + 4;
}

Immediate Issue::issue_auipc(const InstructionBase &inst) {
    auto unit_id = find_available_op_unit();
    if (unit_id == NONE) return pc;

    auto rs = session->e->occupy_unit(unit_id);

    rs->Op = ALUUnit::OP::ADD;
    rs->Tag = issue_cnt;

    issue_imm_to_Vk(pc, rs, unit_id);
    issue_imm_to_Vk(inst.imm, rs, unit_id);

    session->e->rename_register(inst.rd, unit_id);

    return pc + 4;
}

RSID Issue::find_available_unit_in(const std::vector<RSID> &src) {
    for (auto &&unit : src) {
        if (session->e->available(unit)) return unit;
    }
    return NONE;
}

Immediate Issue::issue_jal(const InstructionBase &inst) {
    auto unit_id = find_available_op_unit();
    if (unit_id == NONE) return pc;

    auto rs = session->e->occupy_unit(unit_id);
    rs->Op = ALUUnit::OP::ADD;
    rs->Tag = issue_cnt;

    issue_imm_to_Vk(pc, rs, unit_id);
    issue_imm_to_Vj(4, rs, unit_id);

    session->e->rename_register(inst.rd, unit_id);

    return pc + inst.imm;
}

void Issue::issue_imm_to_A(Immediate imm, RS *rs, RSID) {
    rs->A = imm;
}
