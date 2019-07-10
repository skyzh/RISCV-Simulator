//
// Created by Alex Chi on 2019-07-10.
//

#include "LoadStoreUnit.h"

void LoadStoreUnit::update() {
    // TODO: here we should handle data hazard,
    //       since we only have one functional unit,
    //       we don't need to handle this situation
}

LoadStoreUnit::LoadStoreUnit(OoOExecute *e)
    : e(e), rs_load(LOAD1), rs_store(STORE1) {}
