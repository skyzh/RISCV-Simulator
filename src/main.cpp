#include <iostream>
#include <iomanip>
#include "Session.h"

int main() {
    Session session;
    session.load_memory("../data/expr.data");
    while (true) {
        std::cout << std::hex << session.PC.read() << std::endl;
        session.rf.debug();
        session.tick();
        if (session.memory[0x30004]) {
            break;
        }
    }
    return 0;
}
