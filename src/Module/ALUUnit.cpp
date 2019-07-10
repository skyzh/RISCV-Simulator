//
// Created by Alex Chi on 2019-07-10.
//

#include <cassert>
#include "ALUUnit.h"
#include "../Instruction.hpp"
#include "../Pipeline/OoOExecute.h"

void ALUUnit::update() {
    for (auto &&r_id : rs) {
        RS* r = e->get_rs(r_id);
        if (r->Busy) {
            if (r->Qj == NONE && r->Qk == NONE) {
                Immediate result = get_result(r->Op, r->Vj, r->Vk);
                e->put_result(r_id, result);
                r->Busy = false;
            }
        }
    }
}

Immediate ALUUnit::get_result(Immediate op, Immediate op1, Immediate op2) {
    if (op == ADD) return op1 + op2;
    if (op == SUB) return op1 - op2;
    if (op == SLT) { if ((SImmediate) op1 < (SImmediate) op2) return 1; else return 0; }
    if (op == SLTU) { if (op1 < op2) return 1; else return 0; }
    if (op == XOR) return op1 ^ op2;
    if (op == SRL) return op1 >> (op2 & (unsigned) 0x1f);
    if (op == SLL) return op1 << (op2 & (unsigned) 0x1f);
    if (op == SRA) return (SImmediate) op1 >> (op2 & (unsigned) 0x1f);
    if (op == OR) return op1 | op2;
    if (op == AND) return op1 & op2;
    assert(false);
    return 0;
}

ALUUnit::ALUUnit(OoOExecute *e)
    : e(e), rs({ ADD1, ADD2, ADD3, BRANCH1 }) {}

std::string ALUUnit::resolve(ALUUnit::OP op) {
    switch(op) {
        case ADD: return "ADD";
        case SUB: return "SUB";
        case SLT: return "SLT";
        case SLTU: return "SLTU";
        case XOR: return "XOR";
        case SRL: return "SRL";
        case SLL: return "SLL";
        case SRA: return "SRA";
        case OR: return "OR";
        case AND: return "AND";
        case NONE_OP: return "NONE";
    }
    return "UNKNOWN";
}
