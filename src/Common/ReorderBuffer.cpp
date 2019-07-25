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
              << setw(8) << resolve(Inst.current().opcode);
    debug_immediate(Dest.current(), 7);
    debug_immediate(Value.current(), 11);
    debug_immediate(Tag.current(), 7);
    std::cout << (Inst.current().is_nop() ? "  (⚪idle)" : "");
    std::cout << (Ready.current() ? "  (⚪ready)" : "");
    std::cout << std::endl;
}

void ROB::debug_header() {
    char buffer[100];
    sprintf(buffer, "%4s%8s%16s%24s%16s\n",
            "ID", "Type", "Dest", "Val", "Tag");
    std::cout << buffer;
}
