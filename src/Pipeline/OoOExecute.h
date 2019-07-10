//
// Created by Alex Chi on 2019-07-10.
//

#ifndef RISCV_SIMULATOR_OOOEXECUTE_H
#define RISCV_SIMULATOR_OOOEXECUTE_H

#include "OoOCommon.h"
#include "../ReservationStation.hpp"
#include <memory>

using std::unique_ptr;

class ALUUnit;

class OoOExecute {
public:
    RS Add1, Add2, Add3, Load1, Store1;
    RS *Qi[32];

    unique_ptr <ALUUnit> aluUnit;

    OoOExecute();

    void update();

    void tick();

    void put_result(RSID id, Immediate result);

    RS *get_rs(RSID id);
};


#endif //RISCV_SIMULATOR_OOOEXECUTE_H
