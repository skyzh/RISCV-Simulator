//
// Created by Alex Chi on 2019-07-10.
//

#ifndef RISCV_SIMULATOR_OOOEXECUTE_H
#define RISCV_SIMULATOR_OOOEXECUTE_H

#include "OoOCommon.h"
#include "../ReservationStation.hpp"
#include "../Session.h"
#include "../Register.hpp"
#include <memory>

using std::unique_ptr;

class Session;
class ALUUnit;
class LoadStoreUnit;

class OoOExecute {
public:
    static const unsigned MAX_REG = 32;
    RS Add1, Add2, Add3, Load1, Store1;
    Register<RSID> Qi[MAX_REG];

    unique_ptr <ALUUnit> aluUnit;
    unique_ptr <LoadStoreUnit> loadStoreUnit;

    Session* session;

    OoOExecute(Session* session);

    void update();

    void tick();

    void put_result(RSID id, Immediate result);

    RS *get_rs(RSID id);

    void debug();

    bool available(RSID id);

    bool should_rename_register(unsigned reg_id);

    RSID rename_register(unsigned reg_id, RSID id);
};


#endif //RISCV_SIMULATOR_OOOEXECUTE_H
