//
// Created by Alex Chi on 2019-07-02.
//

#ifndef RISCV_SIMULATOR_SESSION_H
#define RISCV_SIMULATOR_SESSION_H

#include "Tickable.h"

class Fetch;
class Decode;
class Execute;
class Memory;
class WriteBack;

class Session : public Tickable {
public:
    Fetch *f;
    Decode *d;
    Execute *e;
    Memory *m;
    WriteBack *w;

    Session();

    void tick() override;

    virtual ~Session();
};


#endif //RISCV_SIMULATOR_SESSION_H
