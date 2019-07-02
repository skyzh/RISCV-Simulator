//
// Created by Alex Chi on 2019-07-02.
//

#include "gtest/gtest.h"
#include "Memory.hpp"

TEST(Memory, StoreData) {
    Memory mem;
    mem.write(0, 233);
    mem.write(4, 234);
    mem.write(8, 235);
    EXPECT_EQ(mem.read(0), 233);
    EXPECT_EQ(mem.read(4), 234);
    EXPECT_EQ(mem.read(8), 235);
}
