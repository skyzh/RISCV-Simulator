//
// Created by Alex Chi on 2019-07-10.
//

#ifndef RISCV_SIMULATOR_ISSUE_H
#define RISCV_SIMULATOR_ISSUE_H

#include "../Instruction.hpp"
#include "../Register.hpp"

class Session;

class Issue {
public:
    Register<Immediate> pc;

    Session *session;

    Issue(Session *session);

    InstructionBase parse_opcode(unsigned opcode, Immediate imm);

    void issue(const InstructionBase &inst);

    void update();

    void tick();

    void debug();
};


#endif //RISCV_SIMULATOR_ISSUE_H
