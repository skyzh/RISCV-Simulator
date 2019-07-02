//
// Created by Alex Chi on 2019-07-01.
//

#include "gtest/gtest.h"
#include "Parser.hpp"
#include "Memory.hpp"
#include <sstream>

TEST(Parser, Hex) {
    char str[10] = { 0 };
    for (int i = 0; i < 256; i++) {
        if (i % 16 < 10) str[1] = i % 16 + '0';
        else str[1] = i % 16 + 'A' - 10;
        if (i / 16 < 10) str[0] = i / 16 + '0';
        else str[0] = i / 16 + 'A' - 10;
        EXPECT_EQ(Parser::parse_hex(str), (char) i);
    }
}

TEST(Parser, Parse) {
    Memory mem;
    std::string test_data = "@100\n00 01 02 03    \n    04 05\n@0\n06 07 08 09 0A";
    std::stringstream ss(test_data);
    Parser::parse(ss, mem);
    EXPECT_EQ(mem[0x100], 0);
    EXPECT_EQ(mem[0x100 + 1], 1);
    EXPECT_EQ(mem[0x100 + 2], 2);
    EXPECT_EQ(mem[0x100 + 3], 3);
    EXPECT_EQ(mem[0x100 + 4], 4);
    EXPECT_EQ(mem[0x100 + 5], 5);
    EXPECT_EQ(mem[0], 6);
    EXPECT_EQ(mem[1], 7);
    EXPECT_EQ(mem[2], 8);
    EXPECT_EQ(mem[3], 9);
    EXPECT_EQ(mem[4], 10);
}
