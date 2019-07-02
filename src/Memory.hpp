//
// Created by Alex Chi on 2019-07-02.
//

#ifndef RISCV_SIMULATOR_MEMORY_HPP
#define RISCV_SIMULATOR_MEMORY_HPP

#include "Common.h"

const int MEMORY_SIZE = 65536;

class Memory {
public:
    char mem[MEMORY_SIZE];

    Immediate read(unsigned int addr) {
        return *(Immediate *) (mem + addr);
    }
    void write(unsigned int addr, Immediate imm) {
        *(Immediate *) (mem + addr) = imm;
    }
};


#endif //RISCV_SIMULATOR_MEMORY_HPP
