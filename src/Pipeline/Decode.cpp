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

#define NO_VERIFY

Immediate Decode::dispatch(Wire wire) {
    if (!cache_valid[d_inst]) {
        cache_valid[d_inst] = true;
        auto inst = session->f->get(Fetch::inst);
        auto opcode = inst & 0x7f;
        cached_inst = parse_opcode(opcode, inst);
    }
    if (wire == opcode) { return cached_inst.opcode; }
    if (wire == type) return cached_inst.t;

    if (wire == rs1) {
#ifndef NO_VERIFY
        cached_inst.verify("rs1");
#endif
        return cached_inst.rs1;
    }
    if (wire == op1) {
#ifndef NO_VERIFY
        cached_inst.verify("rs1");
#endif
        return session->rf.read(cached_inst.rs1);
    }
    if (wire == rs2) {
#ifndef NO_VERIFY
        cached_inst.verify("rs2");
#endif
        return cached_inst.rs2;
    }
    if (wire == op2) {
#ifndef NO_VERIFY
        cached_inst.verify("rs2");
#endif
        return session->rf.read(cached_inst.rs2);
    }
    if (wire == rd) {
#ifndef NO_VERIFY
        cached_inst.verify("rd");
#endif
        return cached_inst.rd;
    }
    if (wire == funct3) {
#ifndef NO_VERIFY
        cached_inst.verify("funct3");
#endif
        return cached_inst.funct3;
    }
    if (wire == funct7) {
#ifndef NO_VERIFY
        cached_inst.verify("funct7");
#endif
        return cached_inst.funct7;
    }
    if (wire == imm) {
#ifndef NO_VERIFY
        cached_inst.verify("imm");
#endif
        return cached_inst.imm;
    }
    throw InvalidKey();
}

void Decode::tick() {
    Stage::tick();
}
