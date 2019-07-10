//
// Created by Alex Chi on 2019-07-10.
//

#include "Issue.h"

void Issue::update() {
    // Note that pc is register. No matter how
    // many times update is executed, pc always
    // stays the same.
    pc = pc + 4;
}

void Issue::tick() {
    pc.tick();
}

void Issue::issue(const InstructionBase &inst) {

}

Issue::Issue(Session *session) : session(session) {}

InstructionBase Issue::parse_opcode(unsigned opcode, Immediate imm) {
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

void Issue::debug() {

}
