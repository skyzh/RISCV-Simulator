//
// Created by Alex Chi on 2019-07-01.
//

#include "ALU.h"

Immediate ALU::get_i(unsigned opcode, unsigned funct3, Immediate op1, Immediate imm) {
    if (opcode == 0b11) {
        switch (funct3) {
            case 0b000: // LB
            case 0b001: // LH
            case 0b010: // LW
            case 0b100: // LBU
            case 0b101: // LHU
            default:
                throw InvalidOperation();
        }
    }

    if (opcode == 0b10011) {
        switch (funct3) {
            case 0b000: // ADDI
            case 0b010: // SLTI
            case 0b011: // SLTIU
            case 0b100: // XORI
            case 0b110: // ORI
            case 0b111: // ANDI
            default:
                throw InvalidOperation();
        }
    }

    throw InvalidOperation();
}

Immediate ALU::get_s(unsigned opcode, unsigned funct3, Immediate op1, Immediate op2, Immediate imm) {
    if (opcode == 0b100011) {
        switch (funct3) {
            case 0b000: // SB
            case 0b001: // SH
            case 0b010: // SW
            default:
                throw InvalidOperation();
        }
    }

    throw InvalidOperation();
}

Immediate ALU::get_r(unsigned opcode, unsigned funct3, Immediate op1, Immediate op2, unsigned funct7) {
    if (opcode == 0b0010011) {
        switch (funct3) {
            case 0b001: // SLLI
            case 0b101:
                if (funct7 == 0b0000000); // SRLI
                if (funct7 == 0b0100000); // SRAI
            default:
                throw InvalidOperation();
        }
    }

    if (opcode == 0b0110011) {
        switch (funct3) {
            case 0b000:
                if (funct7 == 0b0000000); // ADD
                if (funct7 == 0b0100000); // SUB
            case 0b001: // SLL
            case 0b010: // SLT
            case 0b011: // SLTU
            case 0b100: // XOR
            case 0b101:
                if (funct7 == 0b0000000); // SRL
                if (funct7 == 0b0100000); // SRA
            case 0b110: // OR
            case 0b111: // AND
            default:
                throw InvalidOperation();
        }
    }

    throw InvalidOperation();
}