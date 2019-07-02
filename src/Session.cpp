//
// Created by Alex Chi on 2019-07-02.
//

#include "Session.h"
#include "Pipeline/Fetch.h"
#include "Pipeline/Decode.h"
#include "Pipeline/Execute.h"
#include "Pipeline/Memory.h"
#include "Pipeline/WriteBack.h"

Session::Session() {
    f = new Fetch(this);
    d = new Decode(this);
    e = new Execute(this);
    m = new Memory(this);
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

}

