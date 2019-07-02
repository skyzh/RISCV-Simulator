//
// Created by Alex Chi on 2019-07-01.
//

#ifndef RISCV_SIMULATOR_FETCH_H
#define RISCV_SIMULATOR_FETCH_H

#include "Stage.h"

class Fetch : public Stage {
public:
    Fetch(Session* session);
};


#endif //RISCV_SIMULATOR_FETCH_H
