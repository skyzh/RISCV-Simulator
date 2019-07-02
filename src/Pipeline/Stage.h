//
// Created by Alex Chi on 2019-07-01.
//

#ifndef RISCV_SIMULATOR_STAGE_H
#define RISCV_SIMULATOR_STAGE_H

#include "../Common.h"
#include "../Tickable.h"
#include <map>
#include <string>

class Session;

class Stage : public Tickable {
protected:
    Session *session;
    std::map<std::string, Immediate> cache;
public:
    class InvalidKey {
    };

    Stage(Session *session) : session(session) {}

    virtual void tick() override {
        cache.clear();
    }

    Immediate get(const std::string &key) {
        return this->dispatch(key);
        if (cache.find(key) == cache.end()) {
            cache[key] = this->dispatch(key);
        }
        return cache[key];
    }

    virtual Immediate dispatch(const std::string &key) = 0;
};


#endif //RISCV_SIMULATOR_STAGE_H
