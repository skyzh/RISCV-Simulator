//
// Created by Alex Chi on 2019-07-01.
//

#ifndef RISCV_SIMULATOR_MEMORYACCESS_HPP
#define RISCV_SIMULATOR_MEMORYACCESS_HPP

#include "Stage.hpp"
#include "../Instruction.hpp"
#include "../Register.hpp"

class MemoryAccess : public Stage {
public:
    class InvalidTarget {};
    Register<InstructionBase> m_inst;
    Register<Immediate> m_val, e_val, m_pc;

    MemoryAccess(Session *session);

    void tick();

    void hook();

    void debug();
};


#endif //RISCV_SIMULATOR_MEMORYACCESS_HPP
