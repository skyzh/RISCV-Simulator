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

Immediate WriteBack::dispatch(Wire wire) {
    if (wire == w_pc) {
        auto opcode = session->d->get(Decode::opcode);
        switch(opcode) {
            case 0b1100111: // JALR
            case 0b1101111: // JAL
            case 0b1100011:
                return session->e->get(Execute::e_val);
            default:
                return session->f->get(Fetch::f_pc);
        }
    }
    throw InvalidKey();
}

void WriteBack::tick() {
    Stage::tick();
    write_processed = false;
}

void WriteBack::hook() {
    if (!write_processed) {
        write_processed = true;
        switch (session->d->get(Decode::opcode)) {
            case 0b0110111: // LUI
            case 0b0010111: // AUIPC
            case 0b0010011: // ***I
            case 0b0110011: // ***
                session->rf[session->d->get(Decode::rd)].write(session->e->get(Execute::e_val));
                break;
            case 0b1101111: // JAL
            case 0b1100111: // JALR
                session->rf[session->d->get(Decode::rd)].write(session->f->get(Fetch::f_pc));
                break;
            case 0b0000011: // L*
                session->rf[session->d->get(Decode::rd)].write(session->m->get(MemoryAccess::m_val));
        }
    }
}
