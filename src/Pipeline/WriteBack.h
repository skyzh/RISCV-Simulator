//
// Created by Alex Chi on 2019-07-01.
//

#ifndef RISCV_SIMULATOR_WRITEBACK_H
#define RISCV_SIMULATOR_WRITEBACK_H

#include "Stage.hpp"
#include "../Instruction.hpp"
#include "../Register.hpp"

class WriteBack : public Stage {
public:

    Register<InstructionBase> w_inst;
    Register<Immediate> w_val;

    WriteBack(Session *session);

    void tick();

    void hook();

    void debug();
};

#endif //RISCV_SIMULATOR_WRITEBACK_H
