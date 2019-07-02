//
// Created by Alex Chi on 2019-07-01.
//

#include "WriteBack.h"

WriteBack::WriteBack(Session* session) : Stage(session) {}

Immediate WriteBack::dispatch(const std::string &key) {
    return 0;
}
