//
// Created by Alex Chi on 2019-07-01.
//

#ifndef RISCV_SIMULATOR_STAGE_H
#define RISCV_SIMULATOR_STAGE_H

#include "../Tickable.h"
#include <map>

class Stage : public Tickable {
public:
    void tick() override {}
};


#endif //RISCV_SIMULATOR_STAGE_H
