//
// Created by Alex Chi on 2019-07-01.
//

#include "gtest/gtest.h"
#include "ALU.h"


TEST(ALU, IntegerImmdiateRegisterOperations) {
    ALU alu;
    EXPECT_EQ(alu.get_i(OP_IMM, 0b000, 1, 2), 1 + 2);
    EXPECT_EQ(alu.get_i(OP_IMM, 0b010, 1, 2), 1);
    EXPECT_EQ(alu.get_i(OP_IMM, 0b010, -2, -1), 1);
    EXPECT_EQ(alu.get_i(OP_IMM, 0b011, 1, 2), 1);
    EXPECT_EQ(alu.get_i(OP_IMM, 0b011, 2, 1), 0);
    EXPECT_EQ(alu.get_i(OP_IMM, 0b100, 244, 233), 244 ^ 233);
    EXPECT_EQ(alu.get_i(OP_IMM, 0b110, 244, 233), 244 | 233);
    EXPECT_EQ(alu.get_i(OP_IMM, 0b111, 244, 233), 244 & 233);
    EXPECT_EQ(alu.get_i(OP_IMM, 0b001, 1, 0b00000000100), 1 << 0b100);
    EXPECT_EQ(alu.get_i(OP_IMM, 0b101, -1, 0b01000000100), -1 >> 0b100);
    EXPECT_EQ(alu.get_i(OP_IMM, 0b101, -1, 0b00000000100), (unsigned int) -1 >> 0b100);
}

TEST(ALU, IntegerRegisterRegisterOperations) {
    ALU alu;
    EXPECT_EQ(alu.get_r(OP, 0b000, 1, 2, 0), 1 + 2);
    EXPECT_EQ(alu.get_r(OP, 0b000, 1, 2, 0b0100000), 1 - 2);
    EXPECT_EQ(alu.get_r(OP, 0b010, 1, 2, 0), 1);
    EXPECT_EQ(alu.get_r(OP, 0b010, -2, -1, 0), 1);
    EXPECT_EQ(alu.get_r(OP, 0b011, 1, 2, 0), 1);
    EXPECT_EQ(alu.get_r(OP, 0b011, 2, 1, 0), 0);
    EXPECT_EQ(alu.get_r(OP, 0b100, 244, 233, 0), 244 ^ 233);
    EXPECT_EQ(alu.get_r(OP, 0b110, 244, 233, 0), 244 | 233);
    EXPECT_EQ(alu.get_r(OP, 0b111, 244, 233, 0), 244 & 233);
    EXPECT_EQ(alu.get_r(OP, 0b001, 1, 0b100, 0), 1 << 0b100);
    EXPECT_EQ(alu.get_r(OP, 0b101, -1, 0b100, 0b0100000), -1 >> 0b100);
    EXPECT_EQ(alu.get_r(OP, 0b101, -1, 0b100, 0b0000000), (unsigned int) -1 >> 0b100);
}
