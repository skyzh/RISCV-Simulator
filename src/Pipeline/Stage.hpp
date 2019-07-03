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
    static const int MAX_WIRE = 12;
protected:
    Session *session;
public:
    class InvalidKey {
    };

    Stage(Session *session) : session(session) {}

    virtual void tick() {}

    Immediate get(Wire wire) {
        throw InvalidKey();
    }

    virtual Immediate dispatch(Wire wire) = 0;
};


#endif //RISCV_SIMULATOR_STAGE_HPP
