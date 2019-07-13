//
// Created by Alex Chi on 2019-07-10.
//

#include "LoadStoreUnit.h"
#include "../Common/Instruction.hpp"
#include "../Pipeline/OoOExecute.h"

void LoadStoreUnit::update() {
    for (auto &&r_id : rs_load) {
        RS *r = e->get_rs(r_id);
        if (r->Busy) {
            auto &load_cnt = get_load_cnt_register(r_id);
            // here load takes 3 cycles
            if (load_cnt == 0) {
                unsigned a = r->A;
                if (r->Qj == NONE) {
                    r->A = r->Vj + r->A;
                    load_cnt = 1;
                }
            } else if (load_cnt == 1) {
                unsigned a = r->A;
                if (no_store_in_rob(r->A, r->Dest)) {
                    load_value(r, get_load_buffer(r_id));
                    load_cnt = 2;
                }
            } else if (load_cnt == 2) {
                commit_value(r_id, get_load_buffer(r_id));
                r->Busy = false;
                load_cnt = 0;
            } else
                assert(false);
        }
    }
    for (auto &&r_id : rs_store) {
        RS *r = e->get_rs(r_id);
        if (r->Busy) {
            auto &store_cnt = get_store_cnt_register(r_id);
            if (store_cnt == 0) {
                if (r->Qj == NONE) {
                    e->rob[r->Dest].Dest = r->Vj + r->A;
                    store_cnt = 1;
                }
            } else if (store_cnt == 1) {
                if (r->Qk == NONE) {
                    e->put_result(r_id, r->Vk);
                    r->Busy = false;
                    store_cnt = 0;
                }
            } else
                assert(false);
        }
    }
}

LoadStoreUnit::LoadStoreUnit(OoOExecute *e)
        : e(e), rs_load({LOAD1, LOAD2, LOAD3}), rs_store({STORE1, STORE2, STORE3}) {}

void LoadStoreUnit::load_value(RS *rs, Register<Immediate> &load_buffer) {
    switch (rs->Op) {
        case 0b000: // LB
            load_buffer = (char) e->session->memory[rs->A];
            break;
        case 0b001: // LH
            load_buffer = (short) e->session->memory.read_ushort(rs->A);
            break;
        case 0b010: // LW
            load_buffer = e->session->memory.read_word(rs->A);
            break;
        case 0b100: // LBU
            load_buffer = e->session->memory[rs->A];
            break;
        case 0b101: // LHU
            load_buffer = e->session->memory.read_ushort(rs->A);
            break;
        default:
            assert(false);
    }
}

void LoadStoreUnit::commit_value(RSID r_id, Immediate val) {
    e->put_result(r_id, val);
}

void LoadStoreUnit::tick() {
    for (int i = 0; i < LOAD_BUFFER_SIZE; i++) load_cnt[i].tick();
    for (int i = 0; i < LOAD_BUFFER_SIZE; i++) load_buffer[i].tick();
    for (int i = 0; i < STORE_BUFFER_SIZE; i++) store_cnt[i].tick();
}

bool LoadStoreUnit::no_store_in_rob(unsigned addr, unsigned current_rob) {
    if (current_rob == 0) return true;
    for (unsigned i = e->rob_front; i != current_rob; i = OoOExecute::next_rob_entry(i)) {
        InstructionBase inst = e->rob[i].Inst;
        if (inst.opcode == 0b0100011) { // STORE
            return false;
        }
    }
    return true;
}

void LoadStoreUnit::reset() {
    for (int i = 0; i < LOAD_BUFFER_SIZE; i++) load_cnt[i] = 0;
    for (int i = 0; i < STORE_BUFFER_SIZE; i++) store_cnt[i] = 0;
}

Register<int> &LoadStoreUnit::get_store_cnt_register(RSID r_id) {
    switch (r_id) {
        case STORE1:
            return store_cnt[0];
        case STORE2:
            return store_cnt[1];
        case STORE3:
            return store_cnt[2];
        default:
            assert(false);
    }
}

Register<int> &LoadStoreUnit::get_load_cnt_register(RSID r_id) {
    switch (r_id) {
        case LOAD1:
            return load_cnt[0];
        case LOAD2:
            return load_cnt[1];
        case LOAD3:
            return load_cnt[2];
        default:
            assert(false);
    }
}

Register<Immediate> &LoadStoreUnit::get_load_buffer(RSID r_id) {
    switch (r_id) {
        case LOAD1:
            return load_buffer[0];
        case LOAD2:
            return load_buffer[1];
        case LOAD3:
            return load_buffer[2];
        default:
            assert(false);
    }
}
