//
// Created by Alex Chi on 2019-07-01.
//

#ifndef RISCV_SIMULATOR_EXECUTE_H
#define RISCV_SIMULATOR_EXECUTE_H

#include "Stage.hpp"
#include "../Module/ALU.h"
#include "../Instruction.hpp"
#include "../Register.hpp"

class Execute : public Stage {
private:
    ALU alu;
public:
    Register<InstructionBase> e_inst;
    Register<Immediate> e_val, e_pc, op2;
    bool mis_pred;

    class InvalidAccess {
    };

    class InvalidOp {

    };

    Execute(Session *session);

    void hook();

    void tick();

    void debug();
};


#endif //RISCV_SIMULATOR_EXECUTE_H
