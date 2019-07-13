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
        __rob_flush_flag(false),
        rob_front(1),
        rob_rear(1) {
    aluUnit = new ALUUnit(this);
    loadStoreUnit = new LoadStoreUnit(this);
    commitUnit = new CommitUnit(this);

    for (int i = RS_BEGIN + 1; i < RS_END; i++) {
        RS *rs = get_rs((RSID) i);
        if (rs == nullptr) continue;
        rs->__debug_identifier = i;
    }
    for (int i = 1; i <= ROB_SIZE; i++) {
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
        stat.flush_cycle++;

        for (int i = 0; i < MAX_REG; i++) Busy[i] = false;
        for (int i = 1; i <= ROB_SIZE; i++) {
            rob[i].Ready = false;
            // TODO: set to nop just for more debug information
            rob[i].Inst = InstructionBase::nop();
        }
        for (int i = RS_BEGIN + 1; i < RS_END; i++) {
            RS *rs = get_rs((RSID) i);
            if (rs == nullptr) continue;
            rs->Dest = 0;
            rs->Busy = false;
        }
        rob_front = 1;
        rob_rear = 1;
        __rob_flush_flag = false;
        loadStoreUnit->reset();
        commitUnit->reset();
        aluUnit->reset();
    }
    for (int i = RS_BEGIN + 1; i < RS_END; i++) {
        RS *rs = get_rs((RSID) i);
        if (rs == nullptr) continue;

        if (rs->Busy.current()) stat.unit_busy[i]++;

        rs->tick();
    }
    for (int i = 0; i < MAX_REG; i++) Reorder[i].tick();
    for (int i = 0; i < MAX_REG; i++) Busy[i].tick();
    for (int i = 1; i <= ROB_SIZE; i++) rob[i].tick();

    auto rob_usage_current = (rob_rear - rob_front + ROB_SIZE) % ROB_SIZE;
    stat.rob_usage += rob_usage_current;
    stat.rob_usage_max = std::max(stat.rob_usage_max, rob_usage_current);
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
    if (id == ADD4) return &Add4;
    if (id == LOAD1) return &Load1;
    if (id == LOAD2) return &Load2;
    if (id == LOAD3) return &Load3;
    if (id == STORE1) return &Store1;
    if (id == STORE2) return &Store2;
    if (id == STORE3) return &Store3;
    return nullptr;
}

void OoOExecute::put_result(RSID id, Immediate result) {
    auto from_rs = get_rs(id);
    auto rob_dst = from_rs->Dest;
    if (rob_dst == 0) return;
    rob[rob_dst].Ready = true;
    rob[rob_dst].Value = result;
    for (int i = RS_BEGIN + 1; i < RS_END; i++) {
        RS *rs = get_rs((RSID) i);
        if (rs == nullptr) continue;
        if (rs->Qj.current() == rob_dst) {
            rs->Qj = NONE;
            rs->Vj = result;
        }
        if (rs->Qk.current() == rob_dst) {
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
    std::cout << "front: " << std::dec << rob_front.current() << "\t";
    std::cout << "rear: " << std::dec << rob_rear.current() << std::endl;
    ROB::debug_header();
    for (int i = 1; i <= ROB_SIZE; i++) {
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
    return !get_rs(id)->Busy;
}

RS *OoOExecute::occupy_unit(RSID id) {
    get_rs(id)->Busy = true;
    return get_rs(id);
}

unsigned OoOExecute::acquire_rob() {
    unsigned b = rob_rear;
    if (next_rob_entry(b) == rob_front) return -1;
    rob[b].Ready = false;
    rob_rear = next_rob_entry(b);
    return b;
}

std::vector<unsigned> OoOExecute::acquire_robs(unsigned size) {
    // you should check rob slot yourself
    unsigned b = rob_rear;
    std::vector<unsigned> robs;
    for (int i = 0; i < size; i++, b = next_rob_entry(b)) {
        rob[b].Ready = false;
        robs.push_back(b);
    }
    rob_rear = b;
    return robs;
}

void OoOExecute::occupy_register(unsigned reg_id, unsigned b) {
    if (reg_id == 0) return;
    Reorder[reg_id] = b;
    Busy[reg_id] = true;
}

void OoOExecute::flush_rob() {
    __rob_flush_flag = true;
}

bool OoOExecute::probe_rob(unsigned size) {
    unsigned front = rob_front;
    unsigned rear = rob_rear;
    while (size > 0) {
        auto next_rear = next_rob_entry(rear);
        if (next_rear == front) return false;
        rear = next_rear;
        --size;
    }
    return true;
}

unsigned OoOExecute::next_rob_entry(unsigned id) {
    id++;
    if (id > ROB_SIZE) return id - ROB_SIZE;
    return id;
}

void OoOExecute::report(std::ostream &out) {
    auto total_cycle = session->stat.cycle;
    out << "\t--- Execute Stage Report ---" << std::endl;
    out << "\t" << stat.flush_cycle;
    out << " (" << 100.0 * stat.flush_cycle / total_cycle << "%)";
    out << " cycles with rob flush" << std::endl;
    out << "\t" << stat.correct_branch << " out of " << stat.total_branch << " (" << 100.0 * stat.correct_branch / stat.total_branch << "%) branches predicted" << std::endl;
    out << "\t" << stat.hazard_load << " load hazard detected" << std::endl;
    for (int i = RS_BEGIN + 1; i < RS_END; i++) {
        RS *rs = get_rs((RSID) i);
        if (rs == nullptr) continue;
        out << "\t" << RS::resolve(i) << " busy ";
        out << stat.unit_busy[i];
        out << " (" << 100.0 * stat.unit_busy[i] / total_cycle << "%) cycles" << std::endl;
    }
    out << "\tROB usage mean " << 1.0 * stat.rob_usage / total_cycle << " out of " << ROB_SIZE << std::endl;
    out << "\tROB usage max " << stat.rob_usage_max << " out of " << ROB_SIZE << std::endl;
}

OoOExecute::~OoOExecute() {
    delete aluUnit;
    delete loadStoreUnit;
    delete commitUnit;
}
