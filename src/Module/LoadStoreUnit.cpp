//
// Created by Alex Chi on 2019-07-10.
//

#include "LoadStoreUnit.h"
#include "../Common/Instruction.hpp"
#include "../Pipeline/OoOExecute.h"

void LoadStoreUnit::update() {
    // TODO: here we should handle data hazard,
    //       since we only have one functional unit,
    //       we don't need to handle this situation
    for (auto &&r_id : rs_load) {
        RS *r = e->get_rs(r_id);
        if (r->Busy) {
            // TODO: add more functional unit
            // here load takes 3 cycles
            if (load1_cnt == 0) {
                unsigned a = r->A;
                if (r->Qj == NONE) {
                    r->A = r->Vj + r->A;
                    load1_cnt = 1;
                }
            } else if (load1_cnt == 1) {
                unsigned a = r->A;
                if (no_store_in_rob(r->A, r->Dest)) {
                    load_value(r);
                    load1_cnt = 2;
                }
            } else if (load1_cnt == 2) {
                commit_value(r_id, load1_buffer);
                r->Busy = false;
                load1_cnt = 0;
            } else
                assert(false);
        }
    }
    for (auto &&r_id : rs_store) {
        RS *r = e->get_rs(r_id);
        if (r->Busy) {
            if (store1_cnt == 0) {
                if (r->Qj == NONE) {
                    e->rob[r->Dest].Dest = r->Vj + r->A;
                    store1_cnt = 1;
                }
            } else if (store1_cnt == 1) {
                if (r->Qk == NONE) {
                    e->put_result(r_id, r->Vk);
                    r->Busy = false;
                    store1_cnt = 0;
                }
            } else
                assert(false);
        }
    }
}

LoadStoreUnit::LoadStoreUnit(OoOExecute *e)
        : e(e), rs_load({LOAD1}), rs_store({STORE1}),
          load1_cnt(0), store1_cnt(0) {}

void LoadStoreUnit::load_value(RS *rs) {
    switch (rs->Op) {
        case 0b000: // LB
            load1_buffer = (char) e->session->memory[rs->A];
            break;
        case 0b001: // LH
            load1_buffer = (short) e->session->memory.read_ushort(rs->A);
            break;
        case 0b010: // LW
            load1_buffer = e->session->memory.read_word(rs->A);
            break;
        case 0b100: // LBU
            load1_buffer = e->session->memory[rs->A];
            break;
        case 0b101: // LHU
            load1_buffer = e->session->memory.read_ushort(rs->A);
            break;
        default:
            assert(false);
    }
}

void LoadStoreUnit::commit_value(RSID r_id, Immediate val) {
    e->put_result(r_id, val);
}

void LoadStoreUnit::tick() {
    load1_buffer.tick();
    load1_cnt.tick();
    store1_cnt.tick();
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
