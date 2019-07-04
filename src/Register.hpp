//
// Created by Alex Chi on 2019-07-01.
//

#ifndef RISCV_SIMULATOR_REGISTER_HPP
#define RISCV_SIMULATOR_REGISTER_HPP

#include "Tickable.h"

template<typename T>
class Register { // : public Tickable {
public:
    T prev, next;

    bool _stall;

    Register() : prev(0), next(0), _stall(false) {}

    T read() { return prev; }

    T current() { return next; }

    void write(const T &t) { next = t; }

    void tick() { if (!_stall) prev = next; }

    void stall(bool stall) { _stall = stall; }
};

#endif //RISCV_SIMULATOR_REGISTER_HPP
