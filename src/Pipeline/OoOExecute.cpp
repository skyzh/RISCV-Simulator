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
    aluUnit->update();
    loadStoreUnit->update();
    aluUnit->update();
    loadStoreUnit->update();
}

void OoOExecute::tick() {
    for (int i = RS_BEGIN + 1; i < RS_END; i++) {
        RS *rs = get_rs((RSID) i);
        rs->tick();
    }
    for (int i = 0; i < MAX_REG; i++) Qi[i].tick();
    loadStoreUnit->tick();
}

RS *OoOExecute::get_rs(RSID id) {
    if (id == ADD1) return &Add1;
    if (id == ADD2) return &Add2;
    if (id == ADD3) return &Add3;
    if (id == LOAD1) return &Load1;
    if (id == STORE1) return &Store1;
    if (id == BRANCH1) return &Branch1;
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
        if (rs->Qj.current() == id) {
            rs->Qj = NONE;
            rs->Vj = result;
        }
        if (rs->Qk.current() == id) {
            rs->Qk = NONE;
            rs->Vk = result;
        }
    }
}

void OoOExecute::debug() {
    static const std::vector<const std::string> rf_name = {
            "0", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
            "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5",
            "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7",
            "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6",
            "branch"};
    std::cout << "Reservation Stations" << std::endl;
    for (int i = RS_BEGIN + 1; i < RS_END; i++) {
        RS *rs = get_rs((RSID) i);
        std::cout << rs->resolve(i) << (rs->Busy.current() ? " (busy)" : "") << std::endl;
        rs->debug();
    }
    std::cout << "Register Rename" << std::endl;
    for (int i = 0; i < 4; i++) {
        for (int j = i * 8; j < i * 8 + 8; j++) std::cout << rf_name[j] << "\t\t";
        std::cout << std::endl;
        for (int j = i * 8; j < i * 8 + 8; j++) {
            std::cout << RS::resolve(Qi[j].current());
            std::cout << "\t";
        }
        std::cout << std::endl;
    }
}

bool OoOExecute::available(RSID id) {
    // TODO: we should split load and store logic with speculation
    if (id == STORE1 || id == LOAD1) return !get_rs(LOAD1)->Busy && !get_rs(STORE1)->Busy;
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

RS *OoOExecute::occupy_unit(RSID id) {
    get_rs(id)->Busy = true;
    return get_rs(id);
}
