//
// Created by Alex Chi on 2019-07-01.
//

#include "Decode.h"
#include "../Session.h"
#include "Fetch.h"

Decode::Decode(Session *session) : Stage(session), cache_valid(false) {}

InstructionBase Decode::parse_opcode(unsigned opcode, Immediate imm) {
    if (opcode == 0b0110011) { return InstructionR(imm); } // ***
    if (opcode == 0b0010011) { return InstructionI(imm); } // ***I
    if (opcode == 0b0100011) { return InstructionS(imm); } // S*
    if (opcode == 0b0000011) { return InstructionI(imm); } // L*
    if (opcode == 0b1100011) { return InstructionB(imm); } // B**
    if (opcode == 0b1100111) { return InstructionI(imm); } // JALR
    if (opcode == 0b1101111) { return InstructionJ(imm); } // JAL
    if (opcode == 0b0010111) { return InstructionJ(imm); } // AUIPC
    if (opcode == 0b0110111) { return InstructionJ(imm); } // LUI
    throw InvalidInstruction();
}

Immediate Decode::dispatch(const std::string &key) {
    if (!cache_valid) {
        cache_valid = true;
        auto imm = session->f->get("inst");
        auto opcode = imm & 0x7f;
        cached_inst = parse_opcode(opcode, imm);
    }
    if (key == "opcode") { return cached_inst.opcode; }
    if (key == "type") return cached_inst.t;

    if (key == "rs1") {
        cached_inst.verify("rs1");
        return cached_inst.rs1;
    }
    if (key == "rval1") {
        cached_inst.verify("rs1");
        return session->rf[cached_inst.rs1].read();
    }
    if (key == "rs2") {
        cached_inst.verify("rs2");
        return cached_inst.rs2;
    }
    if (key == "rval2") {
        cached_inst.verify("rs2");
        return session->rf[cached_inst.rs2].read();
    }
    if (key == "rd") {
        cached_inst.verify("rd");
        return cached_inst.rd;
    }
    if (key == "funct3") {
        cached_inst.verify("funct3");
        return cached_inst.funct3;
    }
    if (key == "funct7") {
        cached_inst.verify("funct7");
        return cached_inst.funct7;
    }
    throw InvalidKey();
}

void Decode::tick() {
    Stage::tick();
    cache_valid = false;
}
