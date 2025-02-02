//
// Created by Alex Chi on 2019-07-01.
//

#ifndef RISCV_SIMULATOR_REGISTER_HPP
#define RISCV_SIMULATOR_REGISTER_HPP

template<typename T>
class Register { // : public Tickable {
public:
    T prev, next;

    bool _stall;

    Register() : prev((T) 0), next((T) 0), _stall(false) {}

    Register(T d) : prev(d), next(d), _stall(false) {}

    T read() { return prev; }

    T current() { return next; }

    void write(const T &t) { next = t; }

    void tick() { if (!_stall) prev = next; }

    void stall(bool stall) { _stall = stall; }

    operator T() { return read(); }

    void operator=(T next) { write(next); }
};

#endif //RISCV_SIMULATOR_REGISTER_HPP
