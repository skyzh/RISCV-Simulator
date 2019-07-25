//
// Created by Alex Chi on 2019-07-02.
//

#ifndef RISCV_SIMULATOR_REGISTERFILE_HPP
#define RISCV_SIMULATOR_REGISTERFILE_HPP

#include "Common.h"
#include "Register.hpp"

#include <iostream>
#include <iomanip>
#include <vector>
#include "utils.h"

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
        static std::vector<std::string> rf_name = {"0", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
                                                   "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5",
                                                   "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7",
                                                   "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"};
        for (int i = 0; i < 4; i++) {
            for (int j = i * 8; j < i * 8 + 8; j++) {
                char buffer[20];
                sprintf(buffer, "#%d", j);
                std::cout << std::setw(20) << buffer
                          << std::setw(4) << rf_name[j];
            }
            std::cout << std::endl;
            for (int j = i * 8; j < i * 8 + 8; j++) {
                debug_immediate(next[j], 11);
            }
            std::cout << std::endl;
        }
    }
};


#endif //RISCV_SIMULATOR_REGISTERFILE_HPP
