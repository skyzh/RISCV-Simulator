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

    // Write

    switch (inst.opcode) {
        case 0b0110111: // LUI
        case 0b0010111: // AUIPC
        case 0b0010011: // ***I
        case 0b0110011: // ***
            session->rf.write(inst.rd, session->m->e_val.read());
            break;
        case 0b1101111: // JAL
        case 0b1100111: // JALR
            session->rf.write(inst.rd, session->m->m_pc.read() + 4);
            break;
        case 0b0000011: // L*
            session->rf.write(inst.rd, session->m->m_val.read());
    }
}

void WriteBack::debug() {
    std::cout << "    ";
    w_inst.current().debug();
}
