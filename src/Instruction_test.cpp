//
// Created by Alex Chi on 2019-07-01.
//

#include "gtest/gtest.h"
#include "Instruction.h"

TEST(Instruction, CorrectSize) {
    EXPECT_EQ(sizeof(Instruction), 4);
}
