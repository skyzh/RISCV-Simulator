//
// Created by Alex Chi on 2019-07-12.
//

#include "CommitUnit.h"
#include "../Common/ReorderBuffer.h"
#include "../Pipeline/OoOExecute.h"

CommitUnit::CommitUnit(OoOExecute *e) : e(e) {}

void CommitUnit::update() {
    auto &rob_front = e->rob_front;
    auto &rob_entry = e->rob[rob_front];
    if (rob_entry.Ready) {
        switch (rob_entry.Type) {
            case 0:
                break;
            case 0b0110111: // LUI
            case 0b0010111: // AUIPC
            case 0b1100011: // BRANCH
            case 0b0000011: // LOAD
            case 0b0100011: // STORE
                assert(false);
                break;
            case 0b0010011: // OP-IMM
            case 0b0110011: // OP
            case 0b1101111: // JAL
            case 0b1100111: // JALR
                e->Busy[rob_entry.Dest] = false;
                rob_entry.Ready = false;
                // TODO: this statement can be removed, I add this just
                //       for debug.
                rob_entry.Type = 0;
                e->session->rf.write(rob_entry.Dest, rob_entry.Value);
                break;
            default:
                assert(false);
        }
        rob_front = (rob_front + 1) % e->ROB_SIZE;
    }
}

void CommitUnit::tick() {

}
