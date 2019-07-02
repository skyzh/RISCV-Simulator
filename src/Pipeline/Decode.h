//
// Created by Alex Chi on 2019-07-01.
//

#ifndef RISCV_SIMULATOR_DECODE_H
#define RISCV_SIMULATOR_DECODE_H

#include "Stage.h"

class Decode : public Stage {
public:
    Decode(Session* session);
};


#endif //RISCV_SIMULATOR_DECODE_H
