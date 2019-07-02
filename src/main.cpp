#include <iostream>
#include <iomanip>
#include "Session.h"

void run_session(const char* path, unsigned ret_value) {
    std::cout << "Running: " << path << std::endl;
    Session session;
    session.load_memory(path);
    while (true) {
        session.tick();
        if (session.memory[0x30004]) {
            break;
        }
    }
    assert((session.rf[10].read() & 0xff) == ret_value);
}
int main() {
    /*
    Session session;
    session.load_memory("../data/bulgarian.data");
    while (true) {
        // std::cout << std::hex << session.PC.read() << std::endl;
        if (session.PC.read() == 0x1004) {
            session.tick();
            //session.rf.debug();
            // std::cout << session.rf[10].read() << std::endl;
        } else session.tick();
        if (session.memory[0x30004]) {
            break;
        }
    }
    std::cout << (session.rf[10].read() & 0xff) << std::endl;*/
    // run_session("../data/array_test1.data", 123);
    // run_session("../data/array_test2.data", 43);
    // run_session("../data/basicopt1.data", 88);
    // run_session("../data/bulgarian.data", 159);
    // run_session("../data/expr.data", 58);
    // run_session("../data/gcd.data", 178);
    // run_session("../data/hanoi.data", 20);
    // run_session("../data/lvalue2.data", 175);
    // run_session("../data/magic.data", 106);
    // run_session("../data/manyarguments.data", 40);
    // run_session("../data/multiarray.data", 115);
    run_session("../data/naive.data", 94);
    // run_session("../data/pi.data", 137);
    // run_session("../data/qsort.data", 105);
    // run_session("../data/queens.data", 171);
    // run_session("../data/statement_test.data", 50);
    // run_session("../data/superloop.data", 134);
    // run_session("../data/tak.data", 186);

    return 0;
}
