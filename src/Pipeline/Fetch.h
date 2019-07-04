//
// Created by Alex Chi on 2019-07-01.
//

#ifndef RISCV_SIMULATOR_FETCH_H
#define RISCV_SIMULATOR_FETCH_H

#include "Stage.hpp"
#include "../Register.hpp"
#include "../Instruction.hpp"

class Fetch : public Stage {
public:
    Register<Immediate> pred_pc;
    Register<Immediate> f_pc;
    Register<InstructionBase> f_inst;

    InstructionBase parse_opcode(unsigned opcode, Immediate imm);

    Fetch(Session *session);

    void hook();

    void tick();

    void stall(bool _stall);

    void debug();
};


#endif //RISCV_SIMULATOR_FETCH_H
