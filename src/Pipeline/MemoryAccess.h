//
// Created by Alex Chi on 2019-07-01.
//

#ifndef RISCV_SIMULATOR_MEMORYACCESS_HPP
#define RISCV_SIMULATOR_MEMORYACCESS_HPP

#include "Stage.h"

class MemoryAccess : public Stage {
public:
    MemoryAccess(Session* session);

    Immediate dispatch(const std::string &key) override;
};


#endif //RISCV_SIMULATOR_MEMORYACCESS_HPP
