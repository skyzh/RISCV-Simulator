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

    enum M {
        m_val = 0
    };

    MemoryAccess(Session *session);

    Immediate dispatch(Wire wire) override;

    void tick();

    void hook();
};


#endif //RISCV_SIMULATOR_MEMORYACCESS_HPP
