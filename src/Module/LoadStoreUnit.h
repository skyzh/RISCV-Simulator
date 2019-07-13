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
    static const unsigned LOAD_BUFFER_SIZE = 3;
    static const unsigned STORE_BUFFER_SIZE = 3;
public:
    OoOExecute *e;
    vector<RSID> rs_load, rs_store;

    Register<int> load_cnt[LOAD_BUFFER_SIZE];
    Register<Immediate> load_buffer[LOAD_BUFFER_SIZE];
    Register<int> store_cnt[STORE_BUFFER_SIZE];

    LoadStoreUnit(OoOExecute *e);

    void load_value(RS *rs, Register<Immediate> &load_buffer);

    void commit_value(RSID r_id, Immediate val);

    void update();

    void tick();

    bool no_store_in_rob(unsigned addr, unsigned current_rob);

    void reset();

    Register<int>& get_store_cnt_register(RSID r_id);
    Register<int>& get_load_cnt_register(RSID r_id);
    Register<Immediate>& get_load_buffer(RSID r_id);

};


#endif //RISCV_SIMULATOR_LOADSTOREUNIT_H
