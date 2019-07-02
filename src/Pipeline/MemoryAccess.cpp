//
// Created by Alex Chi on 2019-07-01.
//

#include "MemoryAccess.h"
#include "Decode.h"
#include "Execute.h"
#include "../Session.h"
#include <iostream>

MemoryAccess::MemoryAccess(Session *session) : Stage(session), write_processed(false) {}

Immediate MemoryAccess::dispatch(const std::string &key) {
    if (key == "m_val") {
        unsigned int addr = session->e->get("e_val");
        switch (session->d->get("funct3")) {
            case 0b000: // LB
                return (char) session->memory[addr];
            case 0b001: // LH
                return (short) session->memory.read_ushort(addr);
            case 0b010: // LW
                return session->memory.read_word(addr);
            case 0b100: // LBU
                return session->memory[addr];
            case 0b101: // LHU
                return session->memory.read_ushort(addr);
            default:
                throw InvalidTarget();
        }
    }
    throw InvalidKey();
}

void MemoryAccess::tick() {
    Stage::tick();
    write_processed = false;
}

void MemoryAccess::hook() {
    if (!write_processed) {
        write_processed = true;
        if (session->d->get("opcode") == 0b0100011) {
            unsigned int addr = session->e->get("e_val");
            switch (session->d->get("funct3")) {
                case 0b000: // SB
                    session->memory[addr] = session->d->get("op2");
                    break;
                case 0b001: // SH
                    session->memory.write_ushort(addr, session->d->get("op2"));
                    break;
                case 0b010: // SW
                    session->memory.write_word(addr, session->d->get("op2"));
                    break;
            }
        }
    }
}
