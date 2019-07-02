//
// Created by Alex Chi on 2019-07-01.
//

#ifndef RISCV_SIMULATOR_MEMORY_HPP
#define RISCV_SIMULATOR_MEMORY_H

#include "Stage.h"

class Memory : public Stage {
public:
    Memory(Session* session);
};


#endif //RISCV_SIMULATOR_MEMORY_HPP
