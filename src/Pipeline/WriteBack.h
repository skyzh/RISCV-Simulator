//
// Created by Alex Chi on 2019-07-01.
//

#ifndef RISCV_SIMULATOR_WRITEBACK_H
#define RISCV_SIMULATOR_WRITEBACK_H

#include "Stage.hpp"

class WriteBack : public Stage {
private:
    bool write_processed;
public:
    class InvalidTarget {
    };

    enum W {
        w_pc = 0
    };

    WriteBack(Session *session);

    Immediate dispatch(Wire wire) override;

    void tick() override;

    void hook();
};

#endif //RISCV_SIMULATOR_WRITEBACK_H
