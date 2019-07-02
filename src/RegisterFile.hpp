//
// Created by Alex Chi on 2019-07-02.
//

#ifndef RISCV_SIMULATOR_REGISTERFILE_HPP
#define RISCV_SIMULATOR_REGISTERFILE_HPP

#include "Common.h"
#include "Tickable.h"
#include "Register.hpp"

class RegisterFile : Tickable {
    static const int REG_NUM = 32;
public:
    using Reg_T = Register<Immediate>;

    RegisterFile() : Tickable() {}

    Reg_T reg[REG_NUM];

    Reg_T &operator[](unsigned id) { return reg[id]; }

    void tick() override {
        for (int i = 0; i < REG_NUM; i++) reg[i].tick();
    }
};


#endif //RISCV_SIMULATOR_REGISTERFILE_HPP
