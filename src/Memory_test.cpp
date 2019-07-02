//
// Created by Alex Chi on 2019-07-02.
//

#include "gtest/gtest.h"
#include "Memory.hpp"

TEST(Memory, StoreWord) {
    Memory mem;
    mem.write_word(0, 233);
    mem.write_word(4, 234);
    mem.write_word(8, 235);
    EXPECT_EQ(mem.read_word(0), 233);
    EXPECT_EQ(mem.read_word(4), 234);
    EXPECT_EQ(mem.read_word(8), 235);
}

TEST(Memory, StoreData) {
    Memory mem;
    mem[0] = 233;
    mem[1] = 234;
    mem[2] = 235;
    EXPECT_EQ(mem[0], (char) 233);
    EXPECT_EQ(mem[1], (char) 234);
    EXPECT_EQ(mem[2], (char) 235);
}
