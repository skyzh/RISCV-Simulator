//
// Created by Alex Chi on 2019-07-10.
//

#ifndef RISCV_SIMULATOR_ISSUE_H
#define RISCV_SIMULATOR_ISSUE_H

#include "../Instruction.hpp"
#include "../Register.hpp"
#include "OoOCommon.h"

class Session;

class Issue {
public:
    Register<Immediate> pc;

    InstructionBase _debug_dispatched_inst;

    Session *session;

    Issue(Session *session);

    InstructionBase parse_inst(unsigned opcode, Immediate inst);

    Immediate issue(const InstructionBase &inst);

    void update();

    void tick();

    void debug();

    RSID find_available_op_unit();
};


#endif //RISCV_SIMULATOR_ISSUE_H
