//
// Created by Alex Chi on 2019-07-10.
//

#include <cstring>
#include "OoOExecute.h"
#include "../Module/ALUUnit.h"

using std::make_unique;

OoOExecute::OoOExecute()
    : aluUnit(make_unique<ALUUnit>(this)) {
    memset(Qi, 0, sizeof(Qi));
}

void OoOExecute::update() {

}

void OoOExecute::tick() {

}

RS *OoOExecute::get_rs(RSID id) {
    if (id == ADD1) return &Add1;
    if (id == ADD2) return &Add2;
    if (id == ADD3) return &Add3;
    if (id == LOAD1) return &Load1;
    if (id == STORE1) return &Store1;
    return nullptr;
}

void OoOExecute::put_result(RSID id, Immediate result) {

}
