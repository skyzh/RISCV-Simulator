//
// Created by Alex Chi on 2019-07-10.
//

#include "LoadStoreUnit.h"
#include "../Instruction.hpp"
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
                if (r->Qj == NONE && r->Qk == NONE) {
                    r->A = r->Vj + r->A;
                    load1_cnt = 1;
                }
            } else if (load1_cnt == 1) {
                load_value(r);
                load1_cnt = 2;
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
                if (r->Qj == NONE && r->Qk == NONE) {
                    r->A = r->Vj + r->A;
                    store1_cnt = 1;
                }
            } else if (store1_cnt == 1) {
                write_value(r);
                r->Busy = false;
                store1_cnt = 0;
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

void LoadStoreUnit::write_value(RS *rs) {
    switch (rs->Op) {
        case 0b000: // SB
            e->session->memory[rs->A] = rs->Vk;
            break;
        case 0b001: // SH
            e->session->memory.write_ushort(rs->A, rs->Vk);
            break;
        case 0b010: // SW
            e->session->memory.write_word(rs->A, rs->Vk);
            break;
        default:
            assert(false);
    }
}
