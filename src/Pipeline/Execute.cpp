//
// Created by Alex Chi on 2019-07-01.
//

#include "Execute.h"
#include "Decode.h"
#include "Fetch.h"
#include "../Session.h"

Execute::Execute(Session *session) : Stage(session) {}

Immediate Execute::dispatch(Wire wire) {
    if (wire == e_val) {
        auto type = session->d->get(Decode::type);

        if (type == InstructionBase::Type::R)
            return alu.get_r(
                    session->d->get(Decode::opcode),
                    session->d->get(Decode::funct3),
                    session->d->get(Decode::op1),
                    session->d->get(Decode::op2),
                    session->d->get(Decode::funct7)
            );

        if (type == InstructionBase::Type::I)
            return alu.get_i(
                    session->d->get(Decode::opcode),
                    session->d->get(Decode::funct3),
                    session->d->get(Decode::op1),
                    session->d->get(Decode::imm)
            );

        if (type == InstructionBase::Type::S)
            return alu.get_s(
                    session->d->get(Decode::opcode),
                    session->d->get(Decode::funct3),
                    session->d->get(Decode::op1),
                    session->d->get(Decode::op2),
                    session->d->get(Decode::imm)
            );

        if (type == InstructionBase::Type::B)
            return alu.get_b(
                    session->d->get(Decode::opcode),
                    session->d->get(Decode::funct3),
                    session->d->get(Decode::op1),
                    session->d->get(Decode::op2),
                    session->d->get(Decode::imm),
                    session->f->get(Fetch::f_pc)
            );

        if (type == InstructionBase::Type::J)
            // JAL
            return session->f->get(Fetch::f_pc) + session->d->get(Decode::imm) - 4;

        if (type == InstructionBase::Type::U) {
            switch (session->d->get(Decode::opcode)) {
                case 0b0110111: // LUI
                    return session->d->get(Decode::imm);
                case 0b0010111: // AUIPC
                    return session->f->get(Fetch::f_pc) + session->d->get(Decode::imm) - 4;
                default:
                    throw InvalidOp();
            }
        }

        throw InvalidAccess();
    }

    throw InvalidKey();
}
