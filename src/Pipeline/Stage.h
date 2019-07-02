//
// Created by Alex Chi on 2019-07-01.
//

#ifndef RISCV_SIMULATOR_STAGE_H
#define RISCV_SIMULATOR_STAGE_H

#include "../Tickable.h"
#include <map>

class Session;

class Stage : public Tickable {
private:
    Session *session;
public:
    Stage(Session *session) : session(session) {}

    void tick() override {}
};


#endif //RISCV_SIMULATOR_STAGE_H
