//
// Created by Alex Chi on 2019-07-01.
//

#ifndef RISCV_SIMULATOR_ALU_H
#define RISCV_SIMULATOR_ALU_H

#include "../Instruction.h"

const unsigned OP_IMM = 0b0010011;
const unsigned OP = 0b0110011;

class ALU {
public:
    class InvalidOperation {
    };

    Immediate get_i(unsigned opcode, unsigned funct3, Immediate op1, Immediate imm);

    Immediate get_s(unsigned opcode, unsigned funct3, Immediate op1, Immediate op2, Immediate imm);

    Immediate get_r(unsigned opcode, unsigned funct3, Immediate op1, Immediate op2, unsigned funct7);
};

#endif //RISCV_SIMULATOR_ALU_H
