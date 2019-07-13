//
// Created by Alex Chi on 2019-07-10.
//

#ifndef RISCV_SIMULATOR_OOOEXECUTE_H
#define RISCV_SIMULATOR_OOOEXECUTE_H


#include <memory>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>

#include "OoOCommon.h"
#include "../Common/ReservationStation.h"
#include "../Common/Session.h"
#include "../Common/Register.hpp"
#include "../Common/ReorderBuffer.h"

using std::unique_ptr;

class Session;

class ALUUnit;

class LoadStoreUnit;

class CommitUnit;

class OoOExecute {
public:
    static const unsigned MAX_REG = 32;
    static const unsigned ROB_SIZE = 8;

    struct Stat {
        unsigned long long unit_busy[RS_END];
        unsigned long long flush_cycle;
        unsigned long long rob_usage;
        unsigned rob_usage_max;
        unsigned long long total_branch;
        unsigned long long correct_branch;

        Stat() : flush_cycle(0), rob_usage(0), rob_usage_max(0),
                 total_branch(0), correct_branch(0) {
            memset(unit_busy, 0, sizeof(unit_busy));
        }
    } stat;

    // Reservation Stations
    RS Add1, Add2, Add3, Add4;
    RS Load1, Load2, Load3, Store1, Store2, Store3;

    // Register Rename
    Register<unsigned> Reorder[MAX_REG];
    Register<bool> Busy[MAX_REG];

    // Reorder Buffer (Queue)
    ROB rob[ROB_SIZE + 1];
    Register<unsigned> rob_front, rob_rear;

    ALUUnit *aluUnit;
    LoadStoreUnit *loadStoreUnit;
    CommitUnit *commitUnit;

    Session *session;

    bool __rob_flush_flag;

    OoOExecute(Session *session);

    virtual ~OoOExecute();

    void update();

    void tick();

    void put_result(RSID id, Immediate result);

    RS *get_rs(RSID id);

    void debug();

    bool available(RSID id);

    RS *occupy_unit(RSID id);

    bool probe_rob(unsigned size);

    unsigned acquire_rob();

    std::vector<unsigned> acquire_robs(unsigned size);

    void occupy_register(unsigned reg_id, unsigned b);

    void flush_rob();

    static unsigned next_rob_entry(unsigned id);

    void report(std::ostream &out);
};

#endif //RISCV_SIMULATOR_OOOEXECUTE_H
