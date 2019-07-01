//
// Created by Alex Chi on 2019-07-01.
//

#ifndef RISCV_SIMULATOR_TICKABLE_H
#define RISCV_SIMULATOR_TICKABLE_H

class Tickable {
public:
    virtual void tick() = 0;
};

#endif //RISCV_SIMULATOR_TICKABLE_H
