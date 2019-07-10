//
// Created by Alex Chi on 2019-07-10.
//

#ifndef RISCV_SIMULATOR_RESERVATIONSTATION_HPP
#define RISCV_SIMULATOR_RESERVATIONSTATION_HPP

#include "Register.hpp"
#include "Instruction.hpp"

class RS {
public:
    Register<Immediate> Op, Qj, Qk, Vj, Vk, A;
    Register<bool> Busy;
    RS() : Op(0), Qj(0), Qk(0), Vj(0), Vk(0), A(0), Busy(false) {}

    void tick() {
        Op.tick();
        Qj.tick();
        Qk.tick();
        Vj.tick();
        Vk.tick();
        A.tick();
        Busy.tick();
    }
};

#endif //RISCV_SIMULATOR_RESERVATIONSTATION_HPP
