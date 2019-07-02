//
// Created by Alex Chi on 2019-07-01.
//

#include "Fetch.h"
#include "../Session.h"

Fetch::Fetch(Session* session) : Stage(session) {}

Immediate Fetch::dispatch(const std::string &key) {
    if (key == "inst") {
        return session->memory.read_word(session->PC.read());
    }
    if (key == "f_pc") {
        return session->PC.read() + 4;
    }
    throw InvalidKey();
}
