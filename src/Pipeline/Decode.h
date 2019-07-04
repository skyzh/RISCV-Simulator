//
// Created by Alex Chi on 2019-07-01.
//

#ifndef RISCV_SIMULATOR_DECODE_H
#define RISCV_SIMULATOR_DECODE_H

#include "Stage.hpp"
#include "../Instruction.hpp"
#include "../Register.hpp"

class Decode : public Stage {
private:
    InstructionBase cached_inst;
public:
    Register<InstructionBase> d_inst;
    Register<Immediate> op1, op2;
    Register<Immediate> d_pc, pred_pc;

    bool _bubble, hazard_detected, _stall;

    Decode(Session *session);

    void hook();

    void tick();

    void debug();

    void bubble(bool _bubble);

    void stall(bool _stall);

    bool detect_hazard(unsigned reg_id);
};


#endif //RISCV_SIMULATOR_DECODE_H
