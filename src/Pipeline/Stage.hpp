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
    bool cache_valid[MAX_WIRE];
    Immediate cache[MAX_WIRE];
public:
    class InvalidKey {
    };

    Stage(Session *session) : session(session) {
        reset();
    }

    void reset() {
        memset(cache_valid, 0, sizeof(cache_valid));
        memset(cache, 0, sizeof(cache));
    }

    void tick() { reset(); }

    Immediate get(Wire wire) {
        if (!cache_valid[wire]) {
            cache_valid[wire] = true;
            cache[wire] = this->dispatch(wire);
        }
        return cache[wire];
    }

    virtual Immediate dispatch(Wire wire) = 0;
};


#endif //RISCV_SIMULATOR_STAGE_HPP
