//
// Created by Alex Chi on 2019-07-01.
//

#ifndef RISCV_SIMULATOR_REGISTER_HPP
#define RISCV_SIMULATOR_REGISTER_HPP

#include "Tickable.h"

template<typename T>
class Register : public Tickable {
public:
    T prev, next;

    Register() { prev = next = 0; }

    Register(const T &t) : prev(t), next(t) {}

    const T &read() { return prev; }

    void write(const T &t) { next = t; }

    void tick() { prev = next; }
};

#endif //RISCV_SIMULATOR_REGISTER_HPP