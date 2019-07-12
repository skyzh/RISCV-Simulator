//
// Created by Alex Chi on 2019-07-12.
//

#include "CommitUnit.h"
#include "../Common/ReorderBuffer.h"
#include "../Pipeline/OoOExecute.h"
#include "../Pipeline/Issue.h"

CommitUnit::CommitUnit(OoOExecute *e) : e(e) {}

void CommitUnit::update() {
    auto &rob_front = e->rob_front;
    auto &rob_entry = e->rob[rob_front];
    if (rob_entry.Ready) {
        InstructionBase inst = rob_entry.Inst;
        switch (inst.opcode) {
            case 0:
                break;
            case 0b0110111: // LUI
            case 0b0010111: // AUIPC
            case 0b0000011: // LOAD
            case 0b0100011: // STORE
                assert(false);
                break;
            case 0b1100011: // BRANCH
                resolve_branch(rob_entry);
                break;
            case 0b0010011: // OP-IMM
            case 0b0110011: // OP
            case 0b1101111: // JAL
            case 0b1100111: // JALR
                resolve_op(rob_entry);
                break;
            default:
                assert(false);
        }
        rob_front = (rob_front + 1) % e->ROB_SIZE;
    }
}

void CommitUnit::tick() {

}

void CommitUnit::resolve_branch(ROB &rob_entry) {
    // TODO: since we use always-taken approach,
    //       we can easily figure out whether
    //       we predicted correctly.
    InstructionBase inst = rob_entry.Inst;
    auto pc = rob_entry.Dest;
    auto next_pc = get_next_pc(inst, rob_entry, pc);
    // TODO: for always-not-taken
    if (next_pc != pc + 4) {
        e->flush_rob();
        e->session->i->notify_jump(next_pc);
    }
}

void CommitUnit::resolve_op(ROB &rob_entry) {
    e->Busy[rob_entry.Dest] = false;
    rob_entry.Ready = false;
    // TODO: this statement can be removed, I add this just
    //       for debug.
    rob_entry.Inst = InstructionBase::nop();
    e->session->rf.write(rob_entry.Dest, rob_entry.Value);
}

Immediate CommitUnit::get_next_pc(InstructionBase& inst, ROB& rob_entry, Immediate pc) {
    auto branch_target = pc + inst.imm;
    auto next_inst = pc + 4;
    switch (inst.funct3) {
        case 0b000: // BEQ
            if (rob_entry.Value == 0) return branch_target;
            else return next_inst;
        case 0b001: // BNE
            if (rob_entry.Value != 0) return branch_target;
            else return next_inst;
        case 0b100: // BLT
            if (rob_entry.Value == 1) return branch_target;
            else return next_inst;
        case 0b101: // BGE
            if (rob_entry.Value == 0) return branch_target;
            else return next_inst;
        case 0b110: // BLTU
            if (rob_entry.Value == 1) return branch_target;
            else return next_inst;
        case 0b111: // BGEU
            if (rob_entry.Value == 0) return branch_target;
            else return next_inst;
    }
    assert(false);
    return 0;
}
