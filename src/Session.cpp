//
// Created by Alex Chi on 2019-07-02.
//

#include "Session.h"
#include "Pipeline/Fetch.h"
#include "Pipeline/Decode.h"
#include "Pipeline/Execute.h"
#include "Pipeline/MemoryAccess.h"
#include "Pipeline/WriteBack.h"
#include "Parser.hpp"

#include <fstream>
#include <random>

Session::Session(bool debug) : _debug(debug) {
    f = new Fetch(this);
    d = new Decode(this);
    e = new Execute(this);
    m = new MemoryAccess(this);
    w = new WriteBack(this);
}

Session::~Session() {
    delete f;
    delete d;
    delete e;
    delete m;
    delete w;
}

void Session::tick() {
    w->hook();
    m->hook();
    e->hook();
    d->hook();
    f->hook();

    /*
     * If you want to verify this implementation
     * is really "pipelined", remove the comments,
     * shuffle the hooks in the loop and comment
     * the previous 5 hooks. */

    /*
    for (int i = 0; i < 10; i++) {
        int seq[5] = { 0 };
        for (int j = 0; j < 5; j++) seq[j] = j;
        std::random_shuffle(seq, seq + 5);
        for (int j = 0; j < 5; j++) {
            switch(seq[j]) {
                case 0:
                    f->hook();
                    break;
                case 1:
                    d->hook();
                    break;
                case 2:
                    e->hook();
                    break;
                case 3:
                    m->hook();
                    break;
                case 4:
                    w->hook();
                    break;
            }
        }
    }
     */

    if (_debug) this->debug();

    f->tick();
    d->tick();
    e->tick();
    m->tick();
    w->tick();

    rf.tick();
}

void Session::load_memory(const char *path) {
    std::fstream in(path);
    load_memory(in);
}

void Session::debug() {
    std::cout << "Fetch" << std::endl;
    f->debug();
    std::cout << "Decode" << std::endl;
    d->debug();
    std::cout << "Execute" << std::endl;
    e->debug();
    std::cout << "Memory" << std::endl;
    m->debug();
    std::cout << "Write back" << std::endl;
    w->debug();
    std::cout << "Registers" << std::endl;
    rf.debug();
}

void Session::load_hex(const char *path) {
    std::fstream in(path);
    Parser::parse_hex(in, memory);
}

void Session::load_memory(std::istream &in) {
    Parser::parse(in, memory);
}