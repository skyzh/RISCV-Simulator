//
// Created by Alex Chi on 2019-07-01.
//

#include "Execute.h"
#include "Decode.h"
#include "Fetch.h"
#include "../Session.h"

Execute::Execute(Session *session) : Stage(session) {}

void Execute::tick() {
    auto type = session->d->type;

    if (type == InstructionBase::Type::R)
        e_val = alu.get_r(
                session->d->opcode,
                session->d->funct3,
                session->d->op1,
                session->d->op2,
                session->d->funct7
        );

    if (type == InstructionBase::Type::I)
        e_val = alu.get_i(
                session->d->opcode,
                session->d->funct3,
                session->d->op1,
                session->d->imm
        );

    if (type == InstructionBase::Type::S)
        e_val = alu.get_s(
                session->d->opcode,
                session->d->funct3,
                session->d->op1,
                session->d->op2,
                session->d->imm
        );

    if (type == InstructionBase::Type::B)
        e_val = alu.get_b(
                session->d->opcode,
                session->d->funct3,
                session->d->op1,
                session->d->op2,
                session->d->imm,
                session->f->f_pc
        );

    if (type == InstructionBase::Type::J)
        // JAL
        e_val = session->f->f_pc + session->d->imm - 4;

    if (type == InstructionBase::Type::U) {
        switch (session->d->opcode) {
            case 0b0110111: // LUI
                e_val = session->d->imm;
                break;
            case 0b0010111: // AUIPC
                e_val = session->f->f_pc + session->d->imm - 4;
                break;
        }
    }
}
