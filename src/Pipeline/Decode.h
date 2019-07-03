//
// Created by Alex Chi on 2019-07-01.
//

#ifndef RISCV_SIMULATOR_DECODE_H
#define RISCV_SIMULATOR_DECODE_H

#include "Stage.hpp"
#include "../Instruction.hpp"

class Decode : public Stage {
private:
    InstructionBase cached_inst;
public:
    class InvalidInstruction {
    };

    enum D {
        d_inst = 0, opcode, type, rs1, op1, rs2,
        op2, rd, funct3, funct7, imm
    };

    Decode(Session *session);

    void tick() override;

    Immediate dispatch(Wire wire) override;

    InstructionBase parse_opcode(unsigned opcode, Immediate imm);
};


#endif //RISCV_SIMULATOR_DECODE_H
