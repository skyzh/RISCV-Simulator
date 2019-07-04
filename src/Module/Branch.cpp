//
// Created by Alex Chi on 2019-07-04.
//

#include "Branch.h"
#include <cstring>

Branch::Branch() {
    memset(two_bits, 0, sizeof(two_bits));
    memset(mux, 0, sizeof(mux));
}

bool Branch::take(unsigned addr) {
    return two_bits[addr + (mux[addr] & 0x3)] >= 2;
}

void Branch::report(unsigned addr, bool taken) {
    unsigned branch_addr = addr + (mux[addr] & 0x3);
    if (taken) {
        if (two_bits[branch_addr] < 3) two_bits[branch_addr]++;
    } else {
        if (two_bits[branch_addr] > 0) two_bits[branch_addr]--;
    }
    mux[addr] = mux[addr] << 1 | (taken ? 1 : 0);
}
