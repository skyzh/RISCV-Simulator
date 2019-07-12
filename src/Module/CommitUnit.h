//
// Created by Alex Chi on 2019-07-12.
//

#ifndef RISCV_SIMULATOR_COMMITUNIT_H
#define RISCV_SIMULATOR_COMMITUNIT_H

#include "../Common/ReorderBuffer.h"

class OoOExecute;

class CommitUnit {
public:
    OoOExecute *e;

    CommitUnit(OoOExecute *e);

    void update();

    void tick();

    void resolve_branch(ROB& rob_entry);

    Immediate get_next_pc(InstructionBase& inst, ROB& rob_entry, Immediate pc);
    void resolve_op(ROB& rob_entry);
};


#endif //RISCV_SIMULATOR_COMMITUNIT_H
