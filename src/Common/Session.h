//
// Created by Alex Chi on 2019-07-02.
//

#ifndef RISCV_SIMULATOR_SESSION_H
#define RISCV_SIMULATOR_SESSION_H

#include <iostream>
#include <memory>

#include "Common.h"
#include "Register.hpp"
#include "Memory.hpp"
#include "RegisterFile.hpp"

using std::shared_ptr;

class OoOExecute;

class Issue;

class Session { // : public Tickable {
    bool _debug;
public:
    RegisterFile rf;
    Memory memory;
    OoOExecute *e;
    Issue *i;

    unsigned long long cycle;

    Session(bool debug = false);

    void tick();

    void load_memory(const char *path);

    void load_memory(std::istream &in);

    void load_hex(const char *path);

    virtual ~Session();

    void debug();
};


#endif //RISCV_SIMULATOR_SESSION_H