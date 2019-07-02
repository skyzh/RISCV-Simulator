//
// Created by Alex Chi on 2019-07-01.
//

#include "WriteBack.h"
#include "Decode.h"
#include "Execute.h"
#include "Fetch.h"
#include "../Session.h"

WriteBack::WriteBack(Session *session) : Stage(session), write_processed(false) {}

Immediate WriteBack::dispatch(const std::string &key) {
    if (!write_processed) {
        write_processed = true;
        auto rd = session->d->get("rd");
        switch (session->d->get("opcode")) {
            case 0b0110111: // LUI
                session->rf[rd].write(session->d->get("imm"));
                break;
            case 0b0010111: // AUIPC
            case 0b0000011: // L*
            case 0b0010011: // ***I
            case 0b0110011: // ***
                session->rf[rd].write(session->e->get("e_val"));
                break;
        }
    }

    if (key == "w_pc") {
        if (session->d->get("opcode") == 0b1100011) {
            return session->e->get("e_val");
        } else {
            return session->f->get("f_pc");
        }
    }
    throw InvalidKey();
}

void WriteBack::tick() {
    Stage::tick();
    write_processed = false;
}
