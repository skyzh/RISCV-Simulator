//
// Created by Alex Chi on 2019-07-10.
//

#ifndef RISCV_SIMULATOR_OOOEXECUTE_H
#define RISCV_SIMULATOR_OOOEXECUTE_H

#include "OoOCommon.h"
#include "../Common/ReservationStation.h"
#include "../Common/Session.h"
#include "../Common/Register.hpp"
#include <memory>
#include <vector>
#include <string>

using std::unique_ptr;

class Session;

class ALUUnit;

class LoadStoreUnit;

class OoOExecute {
public:
    static const unsigned MAX_REG = 32 + 1;
    RS Add1, Add2, Add3, Branch1;
    RS Load1, Store1; // These two will be implemented afterwards
    // TODO: Here I added another register to indicate
    //       branch status. It should be eliminated.
    Register<RSID> Qi[MAX_REG];
    static const unsigned BRANCH_REG = MAX_REG - 1;

    unique_ptr<ALUUnit> aluUnit;
    unique_ptr<LoadStoreUnit> loadStoreUnit;

    Session *session;

    OoOExecute(Session *session);

    void update();

    void tick();

    void put_result(RSID id, Immediate result);

    RS *get_rs(RSID id);

    void debug();

    bool available(RSID id);

    bool should_rename_register(unsigned reg_id);

    RSID rename_register(unsigned reg_id, RSID id);

    RSID get_renamed_register(unsigned reg_id);

    RS* occupy_unit(RSID id);
};

#endif //RISCV_SIMULATOR_OOOEXECUTE_H
