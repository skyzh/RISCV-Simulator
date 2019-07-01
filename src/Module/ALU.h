//
// Created by Alex Chi on 2019-07-01.
//

#ifndef RISCV_SIMULATOR_ALU_H
#define RISCV_SIMULATOR_ALU_H

#include "../Instruction.h"

class ALU {
public:
    class InvalidOperation {
    };

    Immediate get_i(unsigned opcode, unsigned funct3, Immediate op1, Immediate imm);

    Immediate get_s(unsigned opcode, unsigned funct3, Immediate op1, Immediate op2, Immediate imm);

    Immediate get_r(unsigned opcode, unsigned funct3, Immediate op1, Immediate op2, unsigned funct7);
};


#endif //RISCV_SIMULATOR_ALU_H
