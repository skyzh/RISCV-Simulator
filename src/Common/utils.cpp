//
// Created by Alex Chi on 2019-07-10.
//

#include "utils.h"
#include <iomanip>
#include <iostream>

void debug_immediate(Immediate v) {
    std::cout << std::dec << v << " (" << std::hex << v << ")";
}
