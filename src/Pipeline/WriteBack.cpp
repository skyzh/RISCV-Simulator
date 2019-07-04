//
// Created by Alex Chi on 2019-07-01.
//

#include "WriteBack.h"
#include "Decode.h"
#include "Execute.h"
#include "Fetch.h"
#include "../Session.h"
#include "MemoryAccess.h"


WriteBack::WriteBack(Session *session) : Stage(session) {}

void WriteBack::tick() {
    w_inst.write(session->m->m_inst.read());
}

void WriteBack::hook() {
    auto inst = session->m->m_inst.read();

    Immediate w_val;
    // Write
    switch (inst.opcode) {
        case 0b0110111: // LUI
        case 0b0010111: // AUIPC
        case 0b0010011: // ***I
        case 0b0110011: // ***
            w_val = session->m->e_val.read();
            session->rf.write(inst.rd, w_val);
            break;
        case 0b1101111: // JAL
        case 0b1100111: // JALR
            w_val = session->m->m_pc.read() + 4;
            session->rf.write(inst.rd, w_val);
            break;
        case 0b0000011: // L*
            w_val = session->m->m_val.read();
            session->rf.write(inst.rd, w_val);
    }
    this->w_val.write(w_val);
}

void WriteBack::debug() {
    std::cout << "    ";
    w_inst.current().debug();
}
