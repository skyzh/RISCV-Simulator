//
// Created by Alex Chi on 2019-07-02.
//

#ifndef RISCV_SIMULATOR_REGISTERFILE_HPP
#define RISCV_SIMULATOR_REGISTERFILE_HPP

#include "Common.h"
#include "Tickable.h"
#include "Register.hpp"

#include <iostream>

class RegisterFile : Tickable {
    static const int REG_NUM = 32;
public:
    using Reg_T = Register<Immediate>;

    RegisterFile() : Tickable() {
        reg[0].always_zero = true;
    }

    Reg_T reg[REG_NUM];

    Reg_T &operator[](unsigned id) { return reg[id]; }

    void tick() override {
        for (int i = 0; i < REG_NUM; i++) reg[i].tick();
    }

    void debug() {
        for (int i = 0; i < 32; i++) {
            std::cout << std::hex << reg[i].read() << " ";
            if ((i + 1) % 8 == 0) std::cout << std::endl;
        }
    }
};


#endif //RISCV_SIMULATOR_REGISTERFILE_HPP
