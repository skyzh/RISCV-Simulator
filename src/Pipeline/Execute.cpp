//
// Created by Alex Chi on 2019-07-01.
//

#include "Execute.h"
#include "Decode.h"
#include "Fetch.h"
#include "../Session.h"

Execute::Execute(Session *session) : Stage(session) {}

void Execute::hook() {
    auto inst = session->d->d_inst.read();
    auto op1 = session->d->op1.read();
    auto op2 = session->d->op2.read();
    auto pc = session->d->d_pc.read();

    e_inst.write(inst);

    Immediate val;
    if (inst.t == InstructionBase::Type::R)
        val = alu.get_r(
                inst.opcode,
                inst.funct3,
                op1,
                op2,
                inst.funct7
        );

    if (inst.t == InstructionBase::Type::I)
        val = alu.get_i(
                inst.opcode,
                inst.funct3,
                op1,
                inst.imm
        );

    if (inst.t == InstructionBase::Type::S)
        val = alu.get_s(
                inst.opcode,
                inst.funct3,
                op1,
                op2,
                inst.imm
        );

    if (inst.t == InstructionBase::Type::B)
        val = alu.get_b(
                inst.opcode,
                inst.funct3,
                op1,
                op2,
                inst.imm,
                pc
        );

    if (inst.t == InstructionBase::Type::J)
        // JAL
        val = pc + inst.imm;

    if (inst.t == InstructionBase::Type::U) {
        switch (inst.opcode) {
            case 0b0110111: // LUI
                val = inst.imm;
                break;
            case 0b0010111: // AUIPC
                val = pc + inst.imm;
                break;
            default:
                throw InvalidOp();
        }
    }

    // Handle mis-prediction
    Immediate next_pc;
    switch(inst.opcode) {
        case 0b1100111: // JALR
        case 0b1101111: // JAL
        case 0b1100011: // B**
            next_pc = val;
            break;
        default:
            next_pc = pc + 4;
    }

    auto pred_pc = session->d->pred_pc.read();

    if (pred_pc != next_pc) {
        mis_pred = true;
    } else {
        mis_pred = false;
    }

    e_val.write(val);

    e_pc.write(pc);

    this->op2.write(op2);
}

void Execute::tick() {
    e_inst.tick();
    e_val.tick();
    e_pc.tick();
    op2.tick();
}

void Execute::debug() {
    std::cout << "    ";
    e_inst.read().debug();
    std::cout << "    " << "e_pc e_val op2 mispred" << std::endl;
    std::cout << "    " << e_pc.read() << " " << e_val.read() << " " << op2.read() << " " << (mis_pred ? "True" : "False") << std::endl;
}
