//
// Created by Alex Chi on 2019-07-01.
//

#include "ALU.h"

Immediate ALU::get_i(unsigned opcode, unsigned funct3, Immediate op1, Immediate imm) {
    if (opcode == 0b11) {
        // Load and Store
        /*
        switch (funct3) {
            case 0b000: // LB
            case 0b001: // LH
            case 0b010: // LW
            case 0b100: // LBU
            case 0b101: // LHU
            default:
                throw InvalidOperation();
        }
         */
        return op1 + imm;
    }
    if (opcode == 0b1100111) {
        return op1 + imm;
    }
    if (opcode == OP_IMM) {
        switch (funct3) {
            case 0b000: // ADDI
                return imm + op1;
            case 0b010: // SLTI
                if ((SImmediate) op1 < (SImmediate) imm) return 1;
                else return 0;
            case 0b011: // SLTIU
                if (op1 < imm) return 1;
                else return 0;
            case 0b100: // XORI
                return op1 ^ imm;
            case 0b110: // ORI
                return op1 | imm;
            case 0b111: // ANDI
                return op1 & imm;
            case 0b001: // SLLI
                return op1 << (imm & (unsigned) 0x1f);
            case 0b101:
                if (imm & (1 << 9)) // SRAI
                    return ((SImmediate) op1) >> (imm & (unsigned) 0x1f);
                else // SRLI
                    return op1 >> (imm & (unsigned) 0x1f);
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

Immediate ALU::get_b(unsigned opcode, unsigned funct3, Immediate op1, Immediate op2, Immediate imm, unsigned pc) {
    if (opcode == 0b1100011) {
        Immediate branch_inst = pc + imm;
        Immediate next_inst = pc + 4;
        switch (funct3) {
            case 0b000: // BEQ
                if (op1 == op2) return branch_inst;
                else return next_inst;
            case 0b001: // BNE
                if (op1 != op2) return branch_inst;
                else return next_inst;
            case 0b100: // BLT
                if ((SImmediate) op1 < (SImmediate) op2) return branch_inst;
                else return next_inst;
            case 0b101: // BGE
                if ((SImmediate) op1 >= (SImmediate) op2) return branch_inst;
                else return next_inst;
            case 0b110: // BLTU
                if (op1 < op2) return branch_inst;
                else return next_inst;
            case 0b111: // BGEU
                if (op1 >= op2) return branch_inst;
                else return next_inst;
            default:
                throw InvalidOperation();
        }
    }
    throw InvalidOperation();
}

Immediate ALU::get_r(unsigned opcode, unsigned funct3, Immediate op1, Immediate op2, unsigned funct7) {
    if (opcode == OP) {
        switch (funct3) {
            case 0b000:
                if (funct7 == 0b0000000) return op1 + op2; // ADD
                if (funct7 == 0b0100000) return op1 - op2; // SUB
            case 0b001: // SLL
                return op1 << (op2 & (unsigned) 0x1f);
            case 0b010: // SLT
                if ((SImmediate) op1 < (SImmediate) op2) return 1;
                else return 0;
            case 0b011: // SLTU
                if (op1 < op2) return 1;
                else return 0;
            case 0b100: // XOR
                return op1 ^ op2;
            case 0b101:
                if (funct7 == 0b0000000) // SRL
                    return op1 >> (op2 & (unsigned) 0x1f);
                if (funct7 == 0b0100000) // SRA
                    return (SImmediate) op1 >> (op2 & (unsigned) 0x1f);
            case 0b110: // OR
                return op1 | op2;
            case 0b111: // AND
                return op1 & op2;
            default:
                throw InvalidOperation();
        }
    }

    throw InvalidOperation();
}