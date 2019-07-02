//
// Created by Alex Chi on 2019-07-01.
//

#ifndef RISCV_SIMULATOR_WRITEBACK_H
#define RISCV_SIMULATOR_WRITEBACK_H

#include "Stage.h"

class WriteBack : public Stage {
private:
    bool write_processed;
public:
    class InvalidTarget {
    };

    WriteBack(Session *session);

    Immediate dispatch(const std::string &key) override;

    void tick() override;
};

#endif //RISCV_SIMULATOR_WRITEBACK_H
