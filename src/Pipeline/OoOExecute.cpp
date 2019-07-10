//
// Created by Alex Chi on 2019-07-10.
//

#include <cstring>
#include "OoOExecute.h"
#include "../Module/ALUUnit.h"
#include "../Module/LoadStoreUnit.h"

using std::make_unique;

OoOExecute::OoOExecute(Session *session) : session(session) {
    aluUnit = make_unique<ALUUnit>(this);
    loadStoreUnit = make_unique<LoadStoreUnit>(this);
    memset(Qi, 0, sizeof(Qi));
}

void OoOExecute::update() {
    aluUnit->update();
    loadStoreUnit->update();
}

void OoOExecute::tick() {
    for (int i = RS_BEGIN + 1; i < RS_END; i++) {
        RS *rs = get_rs((RSID) i);
        rs->tick();
    }
    for (int i = 0; i < MAX_REG; i++) Qi[i].tick();
}

RS *OoOExecute::get_rs(RSID id) {
    if (id == ADD1) return &Add1;
    if (id == ADD2) return &Add2;
    if (id == ADD3) return &Add3;
    if (id == LOAD1) return &Load1;
    if (id == STORE1) return &Store1;
    return nullptr;
}

void OoOExecute::put_result(RSID id, Immediate result) {
    for (int i = 0; i < MAX_REG; i++) {
        if (Qi[i] == id) {
            Qi[i] = NONE;
            session->rf.write(i, result);
        }
    }
    for (int i = RS_BEGIN + 1; i < RS_END; i++) {
        RS *rs = get_rs((RSID) i);
        if (rs->Qj == id) {
            rs->Qj = NONE;
            rs->Vj = result;
        }
        if (rs->Qk == id) {
            rs->Qk = NONE;
            rs->Vk = result;
        }
    }
}

void OoOExecute::debug() {
    for (int i = RS_BEGIN + 1; i < RS_END; i++) {
        RS *rs = get_rs((RSID) i);
        std::cout << rs->resolve(i) << std::endl;
        rs->debug();
    }
}

bool OoOExecute::available(RSID id) {
    return !get_rs(id)->Busy;
}

bool OoOExecute::should_rename_register(unsigned reg_id) {
    return Qi[reg_id] != NONE;
}

RSID OoOExecute::rename_register(unsigned reg_id, RSID id) {
    RSID prev = Qi[reg_id];
    Qi[reg_id] = id;
    return prev;
}
