//
// Created by Alex Chi on 2019-07-11.
//

#include "ReorderBuffer.h"
#include "utils.h"
#include <iostream>
#include <iomanip>

void ROB::debug() {
    using std::cout;
    using std::endl;
    using std::setw;
    std::cout << setw(4) << __debug_identifier
              << setw(8) << resolve(it.current());
    debug_immediate(dst.current(), 7);
    debug_immediate(value.current(), 7);
    std::cout << (ready.current() ? " " : "(⚪busy)") << std::endl;
}

void ROB::debug_header() {
    char buffer[100];
    sprintf(buffer, "%4s%8s%16s%16s\n",
            "ID", "Type", "Dest", "Val");
    std::cout << buffer;
}
