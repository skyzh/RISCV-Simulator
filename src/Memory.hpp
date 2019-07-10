//
// Created by Alex Chi on 2019-07-02.
//

#ifndef RISCV_SIMULATOR_MEMORY_HPP
#define RISCV_SIMULATOR_MEMORY_HPP

#include "Common.h"
#include <cstring>
#include <iostream>

const int MEMORY_SIZE = 0x400000;

class Memory {
public:
    unsigned char mem[MEMORY_SIZE];
    unsigned char placeholder;

    Memory() { memset(mem, 0, sizeof(mem)); }

    bool check_addr(unsigned int addr) {
        if (0 <= addr && addr < MEMORY_SIZE) return true;
        assert(false);
        return false;
    }

    Immediate read_word(unsigned int addr) {
        if (!check_addr(addr)) return 0;
        return *(Immediate *) (mem + addr);
    }

    void write_word(unsigned int addr, Immediate imm) {
        if (!check_addr(addr)) return;
        *(Immediate *) (mem + addr) = imm;
    }

    unsigned short read_ushort(unsigned int addr) {
        if (!check_addr(addr)) return 0;
        return *(short *) (mem + addr);
    }

    void write_ushort(unsigned int addr, unsigned short imm) {
        if (!check_addr(addr)) return;
        *(short *) (mem + addr) = imm;
    }

    unsigned char &operator[](unsigned int addr) {
        if (!check_addr(addr)) return placeholder;
        return mem[addr];
    }

    void debug() {
        for (int i = 0x20000 - 0x10; i <= 0x20000; i++) {
            std::cout << std::hex << (unsigned) mem[i] << " ";
        }
        std::cout << std::endl;
    }
};


#endif //RISCV_SIMULATOR_MEMORY_HPP
