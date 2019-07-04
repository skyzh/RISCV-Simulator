//
// Created by Alex Chi on 2019-07-01.
//

#include "MemoryAccess.h"
#include "Decode.h"
#include "Execute.h"
#include "../Session.h"
#include <iostream>

MemoryAccess::MemoryAccess(Session *session) : Stage(session) {}

void MemoryAccess::tick() {
    m_inst.tick();
    m_val.tick();
    e_val.tick();
    m_pc.tick();
}

void MemoryAccess::hook() {
    auto inst = session->e->e_inst.read();
    auto e_val = session->e->e_val.read();

    if (inst.opcode == 0b0100011) {
        unsigned int addr = e_val;
        Immediate op2 = session->e->op2.read();
        switch (inst.funct3) {
            case 0b000: // SB
                session->memory[addr] = op2;
                break;
            case 0b001: // SH
                session->memory.write_ushort(addr, op2);
                break;
            case 0b010: // SW
                session->memory.write_word(addr, op2);
                break;
        }
    }

    if (inst.opcode == 0b0000011) {
        unsigned int addr = e_val;
        Immediate m_val;

        switch (inst.funct3) {
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
            default:
                throw InvalidTarget();
        }

        this->m_val.write(m_val);
    }

    m_inst.write(inst);

    m_pc.write(session->e->e_pc.read());

    this->e_val.write(e_val);
}

void MemoryAccess::debug() {
    std::cout << "    ";
    m_inst.read().debug();
    std::cout << "    " << "m_pc m_val e_val" << std::endl;
    std::cout << "    " << m_pc.read() << " " << m_val.read() << " " << e_val.read() << std::endl;
}
