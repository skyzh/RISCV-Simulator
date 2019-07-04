//
// Created by Alex Chi on 2019-07-01.
//

#include "Decode.h"
#include "../Session.h"
#include "Fetch.h"

Decode::Decode(Session *session) : Stage(session) {}

void Decode::tick() {
    d_inst.tick();
    op1.tick();
    op2.tick();
    d_pc.tick();
    pred_pc.tick();
}

void Decode::hook() {
    auto f_inst = session->f->f_inst.read();
    if (f_inst.t != InstructionBase::U && f_inst.t != InstructionBase::J)
        op1.write(session->rf.read(f_inst.rs1));
    if (f_inst.t == InstructionBase::R || f_inst.t == InstructionBase::S
        || f_inst.t == InstructionBase::B)
        op2.write(session->rf.read(f_inst.rs2));
    pred_pc.write(session->f->pred_pc.read());
    d_pc.write(session->f->f_pc.read());
    d_inst.write(session->f->f_inst.read());
    // TODO: STALL LOGIC
    /* if rs1 or rs2 not available
     * f->stall_all_reg()
     * set register to bubble mode */
}

void Decode::debug() {
    std::cout << "    ";
    d_inst.read().debug();
    std::cout << "    " << "op1 op2" << std::endl;
    std::cout << "    " << op1.read() << " " << op2.read() << std::endl;
    std::cout << "    " << "d_pc pred_pc" << std::endl;
    std::cout << "    " << d_pc.read() << " " << pred_pc.read() << std::endl;
}
