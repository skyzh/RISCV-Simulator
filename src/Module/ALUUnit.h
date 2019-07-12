//
// Created by Alex Chi on 2019-07-10.
//

#ifndef RISCV_SIMULATOR_ALUUNIT_H
#define RISCV_SIMULATOR_ALUUNIT_H

#include "../Common/ReservationStation.h"
#include "../Pipeline/OoOCommon.h"

#include <vector>
#include <string>

using std::vector;
using std::string;

class OoOExecute;

class ALUUnit {
public:
    OoOExecute *e;
    vector<RSID> rs;
    enum OP {
        NONE_OP = 0, ADD = 233, SUB, SLT, SLTU, XOR, OR, AND, SLL, SRL, SRA
    };

    ALUUnit(OoOExecute *e);

    void update();

    Immediate get_result(Immediate op, Immediate op1, Immediate op2);

    static string resolve(OP op);

    void tick();
};


#endif //RISCV_SIMULATOR_ALUUNIT_H
