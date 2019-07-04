//
// Created by Alex Chi on 2019-07-04.
//

#ifndef RISCV_SIMULATOR_BRANCH_H
#define RISCV_SIMULATOR_BRANCH_H

#include "../Memory.hpp"

class Branch {
public:
    unsigned char two_bits[MEMORY_SIZE];

    Branch();

    bool take(unsigned addr);

    void report(unsigned addr, bool taken);
};


#endif //RISCV_SIMULATOR_BRANCH_H
