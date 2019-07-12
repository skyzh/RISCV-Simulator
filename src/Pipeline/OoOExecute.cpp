//
// Created by Alex Chi on 2019-07-10.
//

#include <cstring>
#include "OoOExecute.h"
#include "../Module/ALUUnit.h"
#include "../Module/LoadStoreUnit.h"
#include "../Module/CommitUnit.h"

using std::make_unique;

OoOExecute::OoOExecute(Session *session) :
    session(session),
    __rob_flush_flag(false) {
    aluUnit = make_unique<ALUUnit>(this);
    loadStoreUnit = make_unique<LoadStoreUnit>(this);
    commitUnit = make_unique<CommitUnit>(this);

    for (int i = RS_BEGIN + 1; i < RS_END; i++) {
        RS *rs = get_rs((RSID) i);
        if (rs == nullptr) continue;
        rs->__debug_identifier = i;
    }
    for (int i = 0; i < ROB_SIZE; i++) {
        rob[i].__debug_identifier = i;
    }
}

void OoOExecute::update() {
    loadStoreUnit->update();
    aluUnit->update();
    commitUnit->update();
}

void OoOExecute::tick() {
    if (__rob_flush_flag) {
        for (int i = 0; i < MAX_REG; i++) Busy[i] = false;
        for (int i = 0; i < ROB_SIZE; i++) {
            rob[i].Ready = false;
            // TODO: set to nop just for more debug information
            rob[i].Inst = InstructionBase::nop();
        }
        for (int i = RS_BEGIN + 1; i < RS_END; i++) {
            RS *rs = get_rs((RSID) i);
            if (rs == nullptr) continue;
            rs->Busy = false;
        }
        rob_front = 0;
        rob_rear = 0;
        __rob_flush_flag = false;
    }
    for (int i = RS_BEGIN + 1; i < RS_END; i++) {
        RS *rs = get_rs((RSID) i);
        if (rs == nullptr) continue;
        rs->tick();
    }
    for (int i = 0; i < MAX_REG; i++) Reorder[i].tick();
    for (int i = 0; i < MAX_REG; i++) Busy[i].tick();
    for (int i = 0; i < ROB_SIZE; i++) rob[i].tick();
    rob_front.tick();
    rob_rear.tick();
    aluUnit->tick();
    loadStoreUnit->tick();
    commitUnit->tick();
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
    auto from_rs = get_rs(id);
    rob[from_rs->Dest].Ready = true;
    rob[from_rs->Dest].Value = result;
    for (int i = RS_BEGIN + 1; i < RS_END; i++) {
        RS *rs = get_rs((RSID) i);
        if (rs == nullptr) continue;
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
    static const std::vector<std::string> rf_name = {
            "0", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
            "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5",
            "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7",
            "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6",
            "branch"};
    std::cout << "Reservation Stations" << std::endl;
    RS::debug_header();
    for (int i = RS_BEGIN + 1; i < RS_END; i++) {
        RS *rs = get_rs((RSID) i);
        if (rs == nullptr) continue;
        rs->debug();
    }
    std::cout << "Reorder Buffer" << std::endl;
    ROB::debug_header();
    for (int i = 0; i < ROB_SIZE; i++) {
        rob[i].debug();
    }
    std::cout << "Register Rename" << std::endl;
    for (int i = 0; i < 4; i++) {
        for (int j = i * 8; j < i * 8 + 8; j++) std::cout << rf_name[j] << "\t\t";
        std::cout << std::endl;
        for (int j = i * 8; j < i * 8 + 8; j++) {
            if (Busy[j].current()) {
                std::cout << "⚪" << Reorder[j].current() << "   \t";
            } else {
                std::cout << "idle" << "\t";
            }
        }
        std::cout << std::endl;
    }
    if (__rob_flush_flag) {
        std::cout << "⭕" << "(rob flush in next cycle)" << std::endl;
    }
}

bool OoOExecute::available(RSID id) {
    // TODO: we should split load and store logic with speculation
    if (id == STORE1 || id == LOAD1) return !get_rs(LOAD1)->Busy && !get_rs(STORE1)->Busy;
    return !get_rs(id)->Busy;
}

RS *OoOExecute::occupy_unit(RSID id) {
    get_rs(id)->Busy = true;
    return get_rs(id);
}

unsigned OoOExecute::acquire_rob() {
    if ((rob_rear + 1) % ROB_SIZE == rob_front) return -1;
    auto b = rob_rear;
    rob_rear = (rob_rear + 1) % ROB_SIZE;
    rob[b].Ready = false;
    return b;
}

void OoOExecute::occupy_register(unsigned reg_id, unsigned b) {
    Reorder[reg_id] = b;
    Busy[reg_id] = true;
}

void OoOExecute::flush_rob() {
    __rob_flush_flag = true;
}
