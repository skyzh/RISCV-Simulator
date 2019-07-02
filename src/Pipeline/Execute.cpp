//
// Created by Alex Chi on 2019-07-01.
//

#include "Execute.h"
#include "Decode.h"
#include "../Session.h"

Execute::Execute(Session *session) : Stage(session) {}

Immediate Execute::dispatch(const std::string &key) {
    if (key == "e_val") {
        auto type = session->d->get("type");
        if (type == InstructionBase::Type::R)
            return alu.get_r(
                    session->d->get("opcode"),
                    session->d->get("funct3"),
                    session->d->get("op1"),
                    session->d->get("op2"),
                    session->d->get("funct7")
            );
        if (type == InstructionBase::Type::I)
            return alu.get_i(
                    session->d->get("opcode"),
                    session->d->get("funct3"),
                    session->d->get("op1"),
                    session->d->get("imm")
            );
        if (type == InstructionBase::Type::S)
            return alu.get_s(
                    session->d->get("opcode"),
                    session->d->get("funct3"),
                    session->d->get("op1"),
                    session->d->get("op2"),
                    session->d->get("imm")
            );
        if (type == InstructionBase::Type::B)
            return alu.get_b(
                    session->d->get("opcode"),
                    session->d->get("funct3"),
                    session->d->get("op1"),
                    session->d->get("op2"),
                    session->d->get("imm"),
                    session->PC.read()
            );
        if (type == InstructionBase::Type::J)
            return session->d->get("imm");
        throw InvalidAccess();
    }

    throw InvalidKey();
}
