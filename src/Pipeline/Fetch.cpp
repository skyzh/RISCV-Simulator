//
// Created by Alex Chi on 2019-07-01.
//

#include "Fetch.h"
#include "../Session.h"

Fetch::Fetch(Session* session) : Stage(session) {}

void Fetch::tick() {
    inst = session->memory.read_word(session->PC.read());
    f_pc = session->PC.read() + 4;
}
