//
// Created by Alex Chi on 2019-07-10.
//

#include "utils.h"
#include <iomanip>
#include <iostream>

void debug_immediate(Immediate v, unsigned width) {
    std::cout << std::dec << std::setw(width) << v << "(" << std::hex << std::setw(width) << v << ")";
}
