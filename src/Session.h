//
// Created by Alex Chi on 2019-07-02.
//

#ifndef RISCV_SIMULATOR_SESSION_H
#define RISCV_SIMULATOR_SESSION_H

#include "Common.h"
#include "Register.hpp"
#include "Tickable.h"
#include "Memory.hpp"

class Fetch;

class Decode;

class Execute;

class MemoryAccess;

class WriteBack;

class Session : public Tickable {
public:
    Fetch *f;
    Decode *d;
    Execute *e;
    MemoryAccess *m;
    WriteBack *w;

    Register<Immediate> PC;
    Memory memory;

    Session();

    void tick() override;

    virtual ~Session();
};


#endif //RISCV_SIMULATOR_SESSION_H
