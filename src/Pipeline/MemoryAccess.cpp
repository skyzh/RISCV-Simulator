//
// Created by Alex Chi on 2019-07-01.
//

#include "MemoryAccess.h"

MemoryAccess::MemoryAccess(Session* session) : Stage(session) {}

Immediate MemoryAccess::dispatch(const std::string &key) {
    throw InvalidKey();
}
