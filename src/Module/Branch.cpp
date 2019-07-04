//
// Created by Alex Chi on 2019-07-04.
//

#include "Branch.h"
#include <cstring>

Branch::Branch() {
    memset(two_bits, 0, sizeof(two_bits));
}

bool Branch::take(unsigned addr) {
    return two_bits[addr] >= 2;
}

void Branch::report(unsigned addr, bool taken) {
    if (taken) {
        if (two_bits[addr] < 3) two_bits[addr]++;
    } else {
        if (two_bits[addr] > 0) two_bits[addr]--;
    }
}
