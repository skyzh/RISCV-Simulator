//
// Created by Alex Chi on 2019-07-01.
//

#ifndef RISCV_SIMULATOR_MEMORYACCESS_HPP
#define RISCV_SIMULATOR_MEMORYACCESS_HPP

#include "Stage.hpp"

class MemoryAccess : public Stage {
private:
    bool write_processed;
public:
    class InvalidTarget {
    };

    Immediate m_val;

    MemoryAccess(Session *session);

    Immediate dispatch(Wire wire) override { throw InvalidKey(); };

    void tick();
};


#endif //RISCV_SIMULATOR_MEMORYACCESS_HPP
