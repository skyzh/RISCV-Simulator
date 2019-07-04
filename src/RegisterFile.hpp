//
// Created by Alex Chi on 2019-07-02.
//

#ifndef RISCV_SIMULATOR_REGISTERFILE_HPP
#define RISCV_SIMULATOR_REGISTERFILE_HPP

#include "Common.h"
#include "Tickable.h"
#include "Register.hpp"

#include <iostream>


class RegisterFile { // : public Tickable {
    static const int REG_NUM = 32;
public:
    Immediate prev[REG_NUM];
    Immediate next[REG_NUM];

    RegisterFile() {
        memset(prev, 0, sizeof(prev));
        memset(next, 0, sizeof(next));
    }

    void tick() { memcpy(prev, next, sizeof(prev)); }

    Immediate read(int id) { return id == 0 ? 0 : prev[id]; }
    void write(int id, Immediate val) { next[id] = val; }

    void debug() {
        for (int i = 0; i < 32; i++) {
            if (i % 8 == 0) std::cout << i << " - " << i + 8 << std::endl;
            std::cout << std::dec << next[i] << std::hex << "(0x" << next[i] << ") ";
            if ((i + 1) % 8 == 0) std::cout << std::endl;
        }
    }
};


#endif //RISCV_SIMULATOR_REGISTERFILE_HPP
