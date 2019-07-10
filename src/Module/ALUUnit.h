//
// Created by Alex Chi on 2019-07-10.
//

#ifndef RISCV_SIMULATOR_ALUUNIT_H
#define RISCV_SIMULATOR_ALUUNIT_H

#include "../ReservationStation.hpp"
#include "../Pipeline/OoOCommon.h"

#include <vector>

using std::vector;

class OoOExecute;

class ALUUnit {
public:
    OoOExecute *e;
    vector<RSID> rs;
    enum OP {
        ADD = 233, SUB, SLT, SLTU, XOR, OR, AND, SLL, SRL, SRA, NONE_OP
    };

    ALUUnit(OoOExecute *e);

    void update();

    Immediate get_result(Immediate op, Immediate op1, Immediate op2);
};


#endif //RISCV_SIMULATOR_ALUUNIT_H
