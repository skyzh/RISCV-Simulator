//
// Created by Alex Chi on 2019-07-02.
//

#include "Session.h"
#include "../Pipeline/Issue.h"
#include "../Pipeline/OoOExecute.h"
#include "../Module/BranchPrediction.h"
#include "Parser.hpp"

#include <thread>
#include <fstream>
#include <random>
#include <functional>

using std::make_shared;

Session::Session(bool debug) : _debug(debug) {
    i = new Issue(this);
    e = new OoOExecute(this);
    branch = new BranchPrediction;
}

Session::~Session() {
    delete i;
    delete e;
    delete branch;
}

void Session::tick() {
    ++stat.cycle;

    i->update();
    e->update();

    if (_debug) this->debug();

    i->tick();
    e->tick();

    rf.tick();
}

void Session::load_memory(const char *path) {
    std::fstream in(path);
    load_memory(in);
}

void Session::debug() {
    std::cout << "   Cycle " << std::dec << stat.cycle << std::endl;
    std::cout << "---- Issue Stage ----" << std::endl;
    i->debug();
    std::cout << "--- Execute Stage ---" << std::endl;
    e->debug();
    std::cout << "----- Registers -----" << std::endl;
    rf.debug();
}

void Session::load_hex(const char *path) {
    std::fstream in(path);
    Parser::parse_hex(in, memory);
}

void Session::load_memory(std::istream &in) {
    Parser::parse(in, memory);
}

void Session::report(std::ostream &out) {
    out << "\t--- Session Report ---" << std::endl;
    out << "\t" << stat.cycle << " Cycles" << std::endl;
    i->report(out);
    e->report(out);
}
