//
// Created by Alex Chi on 2019-07-10.
//

#ifndef RISCV_SIMULATOR_ISSUE_H
#define RISCV_SIMULATOR_ISSUE_H

#include "../Common/Instruction.hpp"
#include "../Common/Register.hpp"
#include "OoOCommon.h"
#include "../Common/ReservationStation.h"

class Session;

class Issue {
public:
    Register<Immediate> pc;
    // TODO: this is used for handling w-w hazard in memory,
    //       should be eliminated once speculation is possible
    Register<long long> issue_cnt;

    bool __jump_flag;
    Immediate __jump_dest;

    InstructionBase _debug_dispatched_inst;

    Session *session;

    Issue(Session *session);

    InstructionBase parse_inst(unsigned opcode, Immediate inst);

    Immediate issue(const InstructionBase &inst);

    void update();

    void tick();

    void debug();

    RSID find_available_unit_in(const std::vector<RSID> &src);

    RSID find_available_op_unit();

    RSID find_available_load_unit();

    RSID find_available_store_unit();

    Immediate issue_branch(const InstructionBase &inst);

    Immediate issue_immediate_op(const InstructionBase &inst);

    Immediate issue_op(const InstructionBase &inst);

    Immediate issue_jalr(const InstructionBase &inst);

    Immediate issue_load(const InstructionBase &inst);

    Immediate issue_store(const InstructionBase &inst);

    Immediate issue_lui(const InstructionBase &inst);

    Immediate issue_auipc(const InstructionBase &inst);

    Immediate issue_jal(const InstructionBase &inst);

    void issue_rs_to_Vj(unsigned reg_id, RS *rs, RSID unit_id);

    void issue_rs_to_Vk(unsigned reg_id, RS *rs, RSID unit_id);

    void issue_imm_to_Vj(Immediate imm, RS *rs, RSID unit_id);

    void issue_imm_to_Vk(Immediate imm, RS *rs, RSID unit_id);

    void issue_imm_to_A(Immediate imm, RS *rs, RSID unit_id);

    void notify_jump(Immediate jump_dest);
};


#endif //RISCV_SIMULATOR_ISSUE_H
