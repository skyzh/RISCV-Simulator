//
// Created by Alex Chi on 2019-07-10.
//

#ifndef RISCV_SIMULATOR_ISSUE_H
#define RISCV_SIMULATOR_ISSUE_H

#include "../Instruction.hpp"
#include "../Register.hpp"
#include "OoOCommon.h"
#include "../ReservationStation.h"

class Session;

class Issue {
public:
    Register<Immediate> pc;
    Register<bool> branch_issued;

    InstructionBase _debug_dispatched_inst;

    Session *session;

    Issue(Session *session);

    InstructionBase parse_inst(unsigned opcode, Immediate inst);

    Immediate issue(const InstructionBase &inst);

    void update();

    void tick();

    void debug();

    RSID find_available_op_unit();

    Immediate issue_branch(const InstructionBase &inst);

    Immediate resolve_branch(const InstructionBase &inst);

    Immediate issue_immediate_op(const InstructionBase &inst);

    Immediate issue_op(const InstructionBase &inst);

    void issue_rs_to_Vj(unsigned reg_id, RS* rs, RSID unit_id);

    void issue_rs_to_Vk(unsigned reg_id, RS* rs, RSID unit_id);

    void issue_imm_to_Vk(Immediate imm, RS* rs, RSID unit_id);
};


#endif //RISCV_SIMULATOR_ISSUE_H
