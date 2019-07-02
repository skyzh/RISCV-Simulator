//
// Created by Alex Chi on 2019-07-01.
//

#include "Decode.h"
#include "../Session.h"

Decode::Decode(Session* session) : Stage(session) {}

Immediate Decode::dispatch(const std::string &key) {
    return 0;
}
