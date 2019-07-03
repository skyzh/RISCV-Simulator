//
// Created by Alex Chi on 2019-07-01.
//

#include "Decode.h"
#include "../Session.h"
#include "Fetch.h"

Decode::Decode(Session *session) : Stage(session) {}

InstructionBase Decode::parse_opcode(unsigned opcode, Immediate imm) {
    if (opcode == 0b0110011) { return InstructionR(imm); } // ***
    if (opcode == 0b0010011) { return InstructionI(imm); } // ***I
    if (opcode == 0b0100011) { return InstructionS(imm); } // S*
    if (opcode == 0b0000011) { return InstructionI(imm); } // L*
    if (opcode == 0b1100011) { return InstructionB(imm); } // B**
    if (opcode == 0b1100111) { return InstructionI(imm); } // JALR
    if (opcode == 0b1101111) { return InstructionJ(imm); } // JAL
    if (opcode == 0b0010111) { return InstructionU(imm); } // AUIPC
    if (opcode == 0b0110111) { return InstructionU(imm); } // LUI
    throw InvalidInstruction();
}

void Decode::tick() {
    auto _inst = session->f->inst;
    auto _opcode = _inst & 0x7f;
    auto inst = parse_opcode(_opcode, _inst);
    opcode = inst.opcode;
    type = inst.t;
    rs1 = inst.rs1;
    rs2 = inst.rs2;
    if (type != InstructionBase::U && type != InstructionBase::J)
        op1 = session->rf.read(rs1);
    if (type == InstructionBase::R || type == InstructionBase::S || type == InstructionBase::B) op2 = session->rf.read(rs2);
    rd = inst.rd;
    funct3 = inst.funct3;
    funct7 = inst.funct7;
    imm = inst.imm;
}
