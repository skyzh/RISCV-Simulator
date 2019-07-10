//
// Created by Alex Chi on 2019-07-10.
//

#ifndef RISCV_SIMULATOR_LOADSTOREUNIT_H
#define RISCV_SIMULATOR_LOADSTOREUNIT_H

#include "../Pipeline/OoOCommon.h"

#include <vector>

using std::vector;

class OoOExecute;

class LoadStoreUnit {
public:
    OoOExecute *e;
    vector<RSID> rs_load, rs_store;

    LoadStoreUnit(OoOExecute *e);

    void update();
};


#endif //RISCV_SIMULATOR_LOADSTOREUNIT_H
