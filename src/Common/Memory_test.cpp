//
// Created by Alex Chi on 2019-07-02.
//

#include "gtest/gtest.h"
#include "Memory.hpp"

TEST(Memory, StoreWord) {
    Memory mem;
    mem.write_word(0, 233);
    mem.write_word(4, -234);
    mem.write_word(8, 235);
    EXPECT_EQ(mem.read_word(0), 233);
    EXPECT_EQ(mem.read_word(4), -234);
    EXPECT_EQ(mem.read_word(8), 235);
}

TEST(Memory, StoreShort) {
    Memory mem;
    mem.write_ushort(0, 233);
    mem.write_ushort(4, -234);
    mem.write_ushort(8, 235);
    EXPECT_EQ(mem.read_ushort(0), 233);
    EXPECT_EQ((short) mem.read_ushort(4), -234);
    EXPECT_EQ(mem.read_ushort(8), 235);
}

TEST(Memory, StoreData) {
    Memory mem;
    mem[0] = 233;
    mem[1] = 234;
    mem[2] = 235;
    EXPECT_EQ(mem[0], (unsigned char) 233);
    EXPECT_EQ(mem[1], (unsigned char) 234);
    EXPECT_EQ(mem[2], (unsigned char) 235);
}

TEST(Memory, Utility) {
    unsigned char x = -1;
    int y = (char) x;
    EXPECT_EQ(y, -1);
}
