//
// Created by Alex Chi on 2019-07-01.
//

#include <cassert>
#include "Fetch.h"
#include "../Session.h"
#include "WriteBack.h"

Fetch::Fetch(Session *session) : Stage(session), _jump(false), _stall(false) {}

InstructionBase Fetch::parse_opcode(unsigned opcode, Immediate imm) {
    if (opcode == 0b0110011) { return InstructionR(imm); } // ***
    if (opcode == 0b0010011) { return InstructionI(imm); } // ***I
    if (opcode == 0b0100011) { return InstructionS(imm); } // S*
    if (opcode == 0b0000011) { return InstructionI(imm); } // L*
    if (opcode == 0b1100011) { return InstructionB(imm); } // B**
    if (opcode == 0b1100111) { return InstructionI(imm); } // JALR
    if (opcode == 0b1101111) { return InstructionJ(imm); } // JAL
    if (opcode == 0b0010111) { return InstructionU(imm); } // AUIPC
    if (opcode == 0b0110111) { return InstructionU(imm); } // LUI
    return InstructionBase::nop();
}

void Fetch::hook() {
    Immediate pc = pred_pc.read();

    if (_jump) {
        pc = this->pc; // branch mispredicted
    }

    f_pc.write(pc);

    pred_pc.write(pc + 4);

    auto _inst = session->memory.read_word(pc);
    auto inst = parse_opcode(_inst & 0x7f, _inst);

    if (inst.opcode == 0b1100011) {
        if (session->branch.take(pc)) {
            pred_pc.write(pc + inst.imm);
        }
    }

    if (inst.t == InstructionBase::J) {
        pred_pc.write(pc + inst.imm);
    }

    f_inst.write(inst);
}

void Fetch::tick() {
    pred_pc.tick();
    f_inst.tick();
    f_pc.tick();
}

void Fetch::stall(bool _stall) {
    pred_pc.stall(_stall);
    f_inst.stall(_stall);
    f_pc.stall(_stall);
    this->_stall = _stall;
}

void Fetch::debug() {
    std::cout << "    ";
    f_inst.current().debug();
    std::cout << "    " << "f_pc\tpred_pc" << std::endl;
    std::cout << "    " << f_pc.current() << "\t" << pred_pc.current() << std::endl;
    if (_stall) std::cout << "(stall)" << std::endl;
}

void Fetch::notify_jump(bool _jump, Immediate pc) {
    this->pc = pc;
    this->_jump = _jump;
}
