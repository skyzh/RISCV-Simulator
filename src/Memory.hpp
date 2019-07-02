//
// Created by Alex Chi on 2019-07-02.
//

#ifndef RISCV_SIMULATOR_MEMORY_HPP
#define RISCV_SIMULATOR_MEMORY_HPP

#include "Common.h"
#include <cstring>

const int MEMORY_SIZE = 0x400000;

class Memory {
public:
    char mem[MEMORY_SIZE];

    Memory() { memset(mem, 0, sizeof(mem)); }

    Immediate read_word(unsigned int addr) {
        return *(Immediate *) (mem + addr);
    }

    void write_word(unsigned int addr, Immediate imm) {
        *(Immediate *) (mem + addr) = imm;
    }

    char &operator[](unsigned int addr) { return mem[addr]; }
};


#endif //RISCV_SIMULATOR_MEMORY_HPP
