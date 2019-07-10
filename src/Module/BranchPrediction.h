//
// Created by Alex Chi on 2019-07-04.
//

#ifndef RISCV_SIMULATOR_BRANCHPREDICTION_H
#define RISCV_SIMULATOR_BRANCHPREDICTION_H

#include "../Memory.hpp"

class BranchPrediction {
public:
    unsigned char two_bits[MEMORY_SIZE];
    unsigned char mux[MEMORY_SIZE];

    BranchPrediction();

    bool take(unsigned addr);

    void report(unsigned addr, bool taken);
};


#endif //RISCV_SIMULATOR_BRANCHPREDICTION_H
