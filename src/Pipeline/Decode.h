//
// Created by Alex Chi on 2019-07-01.
//

#ifndef RISCV_SIMULATOR_DECODE_H
#define RISCV_SIMULATOR_DECODE_H

#include "Stage.h"
#include "../Instruction.h"

class Decode : public Stage {
private:
    bool cache_valid;
    InstructionBase cached_inst;
public:
    Decode(Session* session);

    void tick() override;

    Immediate dispatch(const std::string &key) override;
};


#endif //RISCV_SIMULATOR_DECODE_H
