//
// Created by Alex Chi on 2019-07-10.
//

#ifndef RISCV_SIMULATOR_ISSUE_H
#define RISCV_SIMULATOR_ISSUE_H

#include "../Instruction.hpp"

class Issue {
public:
    void issue(const InstructionBase &inst);
    void update();
    void tick();
};


#endif //RISCV_SIMULATOR_ISSUE_H
