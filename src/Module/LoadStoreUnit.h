//
// Created by Alex Chi on 2019-07-10.
//

#ifndef RISCV_SIMULATOR_LOADSTOREUNIT_H
#define RISCV_SIMULATOR_LOADSTOREUNIT_H

#include "../Pipeline/OoOCommon.h"
#include "../Common/Register.hpp"
#include "../Common/Instruction.hpp"

#include <vector>

using std::vector;

class RS;

class OoOExecute;

class LoadStoreUnit {
public:
    OoOExecute *e;
    vector<RSID> rs_load, rs_store;

    Register<int> load1_cnt;
    Register<int> load1_buffer;
    Register<int> store1_cnt;

    LoadStoreUnit(OoOExecute *e);

    void load_value(RS *rs);

    void commit_value(RSID r_id, Immediate val);

    void update();

    void tick();

    bool no_store_in_rob(unsigned addr, unsigned current_rob);

    void reset();
};


#endif //RISCV_SIMULATOR_LOADSTOREUNIT_H
