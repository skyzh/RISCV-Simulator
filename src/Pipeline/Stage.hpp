//
// Created by Alex Chi on 2019-07-01.
//

#ifndef RISCV_SIMULATOR_STAGE_HPP
#define RISCV_SIMULATOR_STAGE_HPP

#include "../Common.h"
#include "../Tickable.h"
#include <map>
#include <cstring>

class Session;

using Wire = unsigned int;

class Stage { // : public Tickable {
protected:
    Session *session;
public:
    Stage(Session *session) : session(session) {}
};


#endif //RISCV_SIMULATOR_STAGE_HPP
