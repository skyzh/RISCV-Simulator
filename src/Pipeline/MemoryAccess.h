//
// Created by Alex Chi on 2019-07-01.
//

#ifndef RISCV_SIMULATOR_MEMORYACCESS_HPP
#define RISCV_SIMULATOR_MEMORYACCESS_HPP

#include "Stage.h"

class MemoryAccess : public Stage {
private:
    bool write_processed;
public:
    class InvalidTarget {
    };

    MemoryAccess(Session *session);

    Immediate dispatch(const std::string &key) override;

    void tick() override;

    void hook();
};


#endif //RISCV_SIMULATOR_MEMORYACCESS_HPP
