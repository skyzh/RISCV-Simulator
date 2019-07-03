//
// Created by Alex Chi on 2019-07-01.
//

#include "WriteBack.h"
#include "Decode.h"
#include "Execute.h"
#include "Fetch.h"
#include "../Session.h"
#include "MemoryAccess.h"


WriteBack::WriteBack(Session *session) : Stage(session), write_processed(false) {}

void WriteBack::tick() {
    auto opcode = session->d->opcode;
    switch (opcode) {
        case 0b1100111: // JALR
        case 0b1101111: // JAL
        case 0b1100011:
            w_pc = session->e->e_val;
            break;
        default:
            w_pc = session->f->f_pc;
            break;
    }

    switch (session->d->opcode) {
        case 0b0110111: // LUI
        case 0b0010111: // AUIPC
        case 0b0010011: // ***I
        case 0b0110011: // ***
            session->rf.write(session->d->rd, session->e->e_val);
            break;
        case 0b1101111: // JAL
        case 0b1100111: // JALR
            session->rf.write(session->d->rd, session->f->f_pc);
            break;
        case 0b0000011: // L*
            session->rf.write(session->d->rd, session->m->m_val);
    }
}