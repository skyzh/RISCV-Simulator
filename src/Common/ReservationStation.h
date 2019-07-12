//
// Created by Alex Chi on 2019-07-10.
//

#ifndef RISCV_SIMULATOR_RESERVATIONSTATION_H
#define RISCV_SIMULATOR_RESERVATIONSTATION_H

#include "Register.hpp"
#include "Instruction.hpp"
#include "../Pipeline/OoOCommon.h"
#include "utils.h"

#include <iostream>

class RS {
public:
    Register<Immediate> Op, Qj, Qk, Vj, Vk, A, Tag, Dest;
    Register<bool> Busy;
    unsigned __debug_identifier;

    RS() : Op(0), Qj(0), Qk(0), Vj(0), Vk(0), A(0), Tag(0), Dest(0), Busy(false) {}

    void tick() {
        Op.tick();
        Qj.tick();
        Qk.tick();
        Vj.tick();
        Vk.tick();
        Tag.tick();
        A.tick();
        Busy.tick();
        Dest.tick();
    }

    static std::string resolve(Immediate tag) {
        switch (tag) {
            case ADD1:
                return "ADD1";
            case ADD2:
                return "ADD2";
            case ADD3:
                return "ADD3";
            case STORE1:
                return "STORE1";
            case LOAD1:
                return "LOAD1";
            case BRANCH1:
                return "BRANCH1";
            case NONE:
                return "NONE";
        }
        return "UNKNOWN";
    }

    static void debug_header();
    void debug();
};

#endif //RISCV_SIMULATOR_RESERVATIONSTATION_H
