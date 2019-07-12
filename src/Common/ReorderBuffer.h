//
// Created by Alex Chi on 2019-07-11.
//

#ifndef RISCV_SIMULATOR_REORDERBUFFER_H
#define RISCV_SIMULATOR_REORDERBUFFER_H

#include "Register.hpp"
#include <string>

class ROB {
public:
    enum IT {
        IT_NONE = 0, BRANCH, STORE, REGISTER
    };

    Register<IT> it;
    Register<unsigned> dst, value;
    Register<bool> ready;

    unsigned __debug_identifier;

    ROB() : it(IT_NONE), dst(0), value(0), ready(true) {}

    void tick() {
        it.tick();
        dst.tick();
        value.tick();
        ready.tick();
    }

    static void debug_header();

    void debug();

    std::string resolve(IT it) {
        switch (it) {
            case IT_NONE:
                return "NONE";
            case BRANCH:
                return "BRANCH";
            case STORE:
                return "STORE";
            case REGISTER:
                return "REG";
        }
    }
};


#endif //RISCV_SIMULATOR_REORDERBUFFER_H
