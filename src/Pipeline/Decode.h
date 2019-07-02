//
// Created by Alex Chi on 2019-07-01.
//

#ifndef RISCV_SIMULATOR_DECODE_H
#define RISCV_SIMULATOR_DECODE_H

#include "Stage.h"
#include "../Instruction.hpp"

class Decode : public Stage {
private:
    bool cache_valid;
    InstructionBase cached_inst;
public:
    class InvalidInstruction {
    };

    Decode(Session *session);

    void tick() override;

    Immediate dispatch(const std::string &key) override;

    InstructionBase parse_opcode(unsigned opcode, Immediate imm);
};


#endif //RISCV_SIMULATOR_DECODE_H
