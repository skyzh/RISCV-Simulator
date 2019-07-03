//
// Created by Alex Chi on 2019-07-01.
//

#include "MemoryAccess.h"
#include "Decode.h"
#include "Execute.h"
#include "../Session.h"
#include <iostream>

MemoryAccess::MemoryAccess(Session *session) : Stage(session), write_processed(false) {}

void MemoryAccess::tick() {
    Stage::tick();
    if (session->d->opcode == 0b0000011) {
        unsigned int addr = session->e->e_val;
        switch (session->d->funct3) {
            case 0b000: // LB
                m_val = (char) session->memory[addr];
                break;
            case 0b001: // LH
                m_val = (short) session->memory.read_ushort(addr);
                break;
            case 0b010: // LW
                m_val = session->memory.read_word(addr);
                break;
            case 0b100: // LBU
                m_val = session->memory[addr];
                break;
            case 0b101: // LHU
                m_val = session->memory.read_ushort(addr);
                break;
        }
    }

    if (session->d->opcode == 0b0100011) {
        unsigned int addr = session->e->e_val;
        switch (session->d->funct3) {
            case 0b000: // SB
                session->memory[addr] = session->d->op2;
                break;
            case 0b001: // SH
                session->memory.write_ushort(addr, session->d->op2);
                break;
            case 0b010: // SW
                session->memory.write_word(addr, session->d->op2);
                break;
        }
    }
}
