//
// Created by Alex Chi on 2019-07-10.
//

#ifndef RISCV_SIMULATOR_RESERVATIONSTATION_HPP
#define RISCV_SIMULATOR_RESERVATIONSTATION_HPP

#include "Register.hpp"
#include "Instruction.hpp"
#include "Pipeline/OoOCommon.h"
#include "utils.h"

#include <iostream>

class RS {
public:
    Register<Immediate> Op, Qj, Qk, Vj, Vk, A, Tag;
    Register<bool> Busy;

    RS() : Op(0), Qj(0), Qk(0), Vj(0), Vk(0), A(0), Tag(0), Busy(false) {}

    void tick() {
        Op.tick();
        Qj.tick();
        Qk.tick();
        Vj.tick();
        Vk.tick();
        Tag.tick();
        A.tick();
        Busy.tick();
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
            case NONE:
                return "NONE";
        }
        return "UNKNOWN";
    }

    void debug() {
        std::cout << "Busy\tOp\t\t\tQj\t\t\tQk\t\t\tVj\t\t\tVk\t\t\tA\t\t\tTag" << std::endl;
        std::cout << Busy.current() << "\t";
        debug_immediate(Op.current());
        std::cout << "\t";
        std::cout << resolve(Qj.current());
        std::cout << "\t";
        std::cout << resolve(Qk.current());
        std::cout << "\t";
        debug_immediate(Vj.current());
        std::cout << "\t";
        debug_immediate(Vk.current());
        std::cout << "\t";
        debug_immediate(A.current());
        std::cout << "\t";
        debug_immediate(Tag.current());

    }
};

#endif //RISCV_SIMULATOR_RESERVATIONSTATION_HPP
