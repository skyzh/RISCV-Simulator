//
// Created by Alex Chi on 2019-07-01.
//

#include "Decode.h"
#include "../Session.h"
#include "Fetch.h"
#include "MemoryAccess.h"
#include "Execute.h"
#include "WriteBack.h"

Decode::Decode(Session *session) : Stage(session), _bubble(false), hazard_detected(false), _stall(false) {}

void Decode::tick() {
    d_inst.tick();
    op1.tick();
    op2.tick();
    d_pc.tick();
    pred_pc.tick();
}

void Decode::hook() {
    if (_bubble) {
        d_inst.write(InstructionBase::nop());
        return;
    }
    auto f_inst = session->f->f_inst.read();

    pred_pc.write(session->f->pred_pc.read());
    d_pc.write(session->f->f_pc.read());
    d_inst.write(session->f->f_inst.read());

    // Detect data hazard
    // Write op1 and op2

    hazard_detected = false;

    if (f_inst.has_op1()) {
        bool may_forward;
        Immediate forward_val;
        Immediate op = 0;
        if (detect_hazard(f_inst.rs1, may_forward, forward_val)) {
            if (may_forward)
                op = forward_val;
            else
                hazard_detected = true;
        } else op = session->rf.read(f_inst.rs1);
        op1.write(op);
    }

    if (f_inst.has_op2()) {
        bool may_forward;
        Immediate forward_val;
        Immediate op = 0;
        if (detect_hazard(f_inst.rs2, may_forward, forward_val)) {
            if (may_forward)
                op = forward_val;
            else
                hazard_detected = true;
        } else op = session->rf.read(f_inst.rs2);
        op2.write(op);
    }


    session->f->stall(hazard_detected);
    bubble(hazard_detected);
}

void Decode::debug() {
    std::cout << "    ";
    d_inst.current().debug();
    std::cout << "    " << "op1\top2" << std::endl;
    std::cout << "    " << op1.current() << "\t" << op2.current() << std::endl;
    std::cout << "    " << "d_pc\tpred_pc" << std::endl;
    std::cout << "    " << d_pc.current() << "\t" << pred_pc.current() << std::endl;
    if (_bubble) std::cout << "(bubble)" << std::endl;
    if (hazard_detected) std::cout << "(hazard detected)" << std::endl;
}

void Decode::bubble(bool _bubble) {
    this->_bubble = _bubble;
    if (_bubble) d_inst.write(InstructionBase::nop());
}

bool Decode::detect_hazard(unsigned reg_id, bool &may_forward, Immediate &forward_val) {
    if (reg_id == 0) return false;
    auto m_inst = session->m->m_inst.current();
    auto e_inst = session->e->e_inst.current();
    auto w_inst = session->w->w_inst.current();
    may_forward = false;
    if (e_inst.rd == reg_id) {
        if (e_inst.opcode == 0b0010011 || e_inst.opcode == 0b0110011) {
            may_forward = true;
            forward_val = session->e->e_val.current();
        }
        return true;
    }
    if (m_inst.rd == reg_id) {
        if (m_inst.opcode == 0b0000011) {
            may_forward = true;
            forward_val = session->m->m_val.current();
        }
        if (m_inst.opcode == 0b0010011 || m_inst.opcode == 0b0110011) {
            may_forward = true;
            forward_val = session->m->e_val.current();
        }
        return true;
    }
    if (w_inst.rd == reg_id) {
        may_forward = true;
        forward_val = session->w->w_val.current();
        return true;
    }
    return false;
}

void Decode::stall(bool _stall) {
    this->_stall = _stall;
    d_inst.stall(_stall);
    op1.stall(_stall);
    op2.stall(_stall);
    d_pc.stall(_stall);
    pred_pc.stall(_stall);
}
