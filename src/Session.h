//
// Created by Alex Chi on 2019-07-02.
//

#ifndef RISCV_SIMULATOR_SESSION_H
#define RISCV_SIMULATOR_SESSION_H

#include <iostream>

#include "Common.h"
#include "Register.hpp"
#include "Tickable.h"
#include "Memory.hpp"
#include "RegisterFile.hpp"

class Fetch;

class Decode;

class Execute;

class MemoryAccess;

class WriteBack;

class Session { // : public Tickable {
    bool _debug;
public:
    Fetch *f;
    Decode *d;
    Execute *e;
    MemoryAccess *m;
    WriteBack *w;

    RegisterFile rf;
    Memory memory;

    Session(bool debug = false);

    void tick();

    void load_memory(const char* path);

    void load_memory(std::istream& in);

    void load_hex(const char* path);

    virtual ~Session();

    void debug();
};


#endif //RISCV_SIMULATOR_SESSION_H
