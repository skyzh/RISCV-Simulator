#include <iostream>
#include <iomanip>
#include "Session.h"
#include <cassert>

void run_session(const char* path, unsigned ret_value) {
    std::cout << "Running: " << path << std::endl;
    Session* session = new Session;
    session->load_memory(path);
    while (true) {
        session->tick();
        if (session->memory[0x30004]) {
            break;
        }
    }
    assert((session->rf[10].read() & 0xff) == ret_value);
    delete session;
}

int run_all_tests() {
    run_session("../data/array_test1.data", 123);
    run_session("../data/array_test2.data", 43);
    run_session("../data/basicopt1.data", 88);
    run_session("../data/bulgarian.data", 159);
    run_session("../data/expr.data", 58);
    run_session("../data/gcd.data", 178);
    run_session("../data/hanoi.data", 20);
    run_session("../data/lvalue2.data", 175);
    run_session("../data/magic.data", 106);
    run_session("../data/manyarguments.data", 40);
    run_session("../data/multiarray.data", 115);
    run_session("../data/naive.data", 94);
    run_session("../data/qsort.data", 105);
    run_session("../data/queens.data", 171);
    run_session("../data/statement_test.data", 50);
    run_session("../data/superloop.data", 134);
    run_session("../data/tak.data", 186);
    run_session("../data/pi.data", 137);
    return 0;
}

int main() {
    run_all_tests();
    return 0;
}
