//
// Created by Alex Chi on 2019-07-10.
//

#ifndef RISCV_SIMULATOR_OOOEXECUTE_H
#define RISCV_SIMULATOR_OOOEXECUTE_H

#include "OoOCommon.h"
#include "../Common/ReservationStation.h"
#include "../Common/Session.h"
#include "../Common/Register.hpp"
#include "../Common/ReorderBuffer.h"
#include <memory>
#include <vector>
#include <string>

using std::unique_ptr;

class Session;

class ALUUnit;

class LoadStoreUnit;

class CommitUnit;

class OoOExecute {
public:
    static const unsigned MAX_REG = 32;
    static const unsigned ROB_SIZE = 4;
    RS Add1, Add2, Add3, Branch1;
    RS Load1, Store1; // These two will be implemented afterwards
    Register<unsigned> Reorder[MAX_REG];
    Register<bool> Busy[MAX_REG];
    // TODO: Here I added another register to indicate
    //       branch status. It should be eliminated.

    ROB rob[ROB_SIZE];
    Register <unsigned> rob_front, rob_rear;

    unique_ptr<ALUUnit> aluUnit;
    unique_ptr<LoadStoreUnit> loadStoreUnit;
    unique_ptr<CommitUnit> commitUnit;

    Session *session;

    bool __rob_flush_flag;

    OoOExecute(Session *session);

    void update();

    void tick();

    void put_result(RSID id, Immediate result);

    RS *get_rs(RSID id);

    void debug();

    bool available(RSID id);

    RS* occupy_unit(RSID id);

    unsigned acquire_rob();

    void occupy_register(unsigned reg_id, unsigned b);

    void flush_rob();
};

#endif //RISCV_SIMULATOR_OOOEXECUTE_H
