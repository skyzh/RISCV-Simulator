//
// Created by Alex Chi on 2019-07-01.
//

#include "Decode.h"
#include "../Session.h"
#include "Fetch.h"

Decode::Decode(Session* session) : Stage(session), cache_valid(false) {}

Immediate Decode::dispatch(const std::string &key) {
    if (!cache_valid) {
        cache_valid = true;
        auto imm = session->f->get("inst");
        // cached_inst = ;
    }
    if (key == "opcode") { return cached_inst.opcode; }
    if (key == "rs1") { return cached_inst.rs1; }
    if (key == "rval1") { return session->rf[cached_inst.rs1].read(); }
    if (key == "rs2") {return cached_inst.rs2;}
    if (key == "rval2") {}
    if (key == "rd") {}
    if (key == "funct3") {}
    if (key == "funct7") {}
    throw InvalidKey();
}

void Decode::tick() {
    Stage::tick();
    cache_valid = false;
}
