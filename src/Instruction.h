//
// Created by Alex Chi on 2019-07-01.
//

#ifndef RISCV_SIMULATOR_INSTRUCTION_H
#define RISCV_SIMULATOR_INSTRUCTION_H

#include <utility>

using Instruction = unsigned int;

struct InstructionBase {
};

constexpr unsigned int bin_mask(int digits) {
    return (1 << digits) - 1;
}

unsigned int get_digits(unsigned int n, int hi, int lo) {
    return (n >> lo) & bin_mask(hi - lo + 1);
}

unsigned int expand_digit(unsigned int digit, int lo) {
    return digit ? (0xffffffff << lo) : 0;
}

struct InstructionR : InstructionBase {
    unsigned opcode, rd, funct3, rs1, rs2, funct7;

    InstructionR(const Instruction &inst) {
        opcode = get_digits(inst, 6, 0);
        rd = get_digits(inst, 11, 7);
        funct3 = get_digits(inst, 14, 12);
        rs1 = get_digits(inst, 19, 15);
        rs2 = get_digits(inst, 24, 20);
        funct7 = get_digits(inst, 31, 25);
    }
};

struct InstructionI : InstructionBase {
    unsigned opcode, rd, funct3, rs1, imm;

    InstructionI(const Instruction &inst) {
        opcode = get_digits(inst, 6, 0);
        rd = get_digits(inst, 11, 7);
        funct3 = get_digits(inst, 14, 12);
        rs1 = get_digits(inst, 19, 15);
        imm = get_digits(inst, 30, 20) | expand_digit(get_digits(inst, 31, 31), 11);
    }
};

struct InstructionS : InstructionBase {
    unsigned opcode, funct3, rs1, rs2, imm;

    InstructionS(const Instruction &inst) {
        opcode = get_digits(inst, 6, 0);
        funct3 = get_digits(inst, 14, 12);
        rs1 = get_digits(inst, 19, 15);
        rs2 = get_digits(inst, 24, 20);
        imm = (get_digits(inst, 11, 7)) |
              (get_digits(inst, 30, 25) << 5) |
              expand_digit(get_digits(inst, 31, 31), 11);
    }
};

struct InstructionB : InstructionBase {
    unsigned opcode, funct3, rs1, rs2, imm;

    InstructionB(const Instruction &inst) {
        opcode = get_digits(inst, 6, 0);
        funct3 = get_digits(inst, 14, 12);
        rs1 = get_digits(inst, 19, 15);
        rs2 = get_digits(inst, 24, 20);
        imm = (get_digits(inst, 11, 8) << 1) |
              (get_digits(inst, 30, 25) << 5) |
              (get_digits(inst, 7, 7) << 11) |
              expand_digit(get_digits(inst, 31, 31), 12);
    }
};

struct InstructionU : InstructionBase {
    unsigned opcode, rd, imm;

    InstructionU(const Instruction &inst) {
        opcode = get_digits(inst, 6, 0);
        rd = get_digits(inst, 11, 7);
        imm = (get_digits(inst, 19, 12) << 12) |
              (get_digits(inst, 30, 20) << 20) |
              (get_digits(inst, 31, 31) << 31);
    }
};

struct InstructionJ : InstructionBase {
    unsigned opcode, rd, imm;

    InstructionJ(const Instruction &inst) {
        opcode = get_digits(inst, 6, 0);
        rd = get_digits(inst, 11, 7);
        imm = (get_digits(inst, 30, 21) << 1) |
              (get_digits(inst, 20, 20) << 11) |
              (get_digits(inst, 19, 12) << 12) |
              expand_digit(get_digits(inst, 31, 31), 20);
    }
};

#endif //RISCV_SIMULATOR_INSTRUCTION_H
