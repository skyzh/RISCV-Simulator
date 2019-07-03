//
// Created by Alex Chi on 2019-07-02.
//

#include "gtest/gtest.h"
#include "RegisterFile.hpp"


TEST(RegisterFile, ReadWrite) {
    RegisterFile r;
    r.write(0, 2333);
    EXPECT_EQ(r.read(0), 0);
    r.write(1, 1);
    EXPECT_EQ(r.read(1), 0);
    r.tick();
    EXPECT_EQ(r.read(1), 1);
    EXPECT_EQ(r.read(0), 0);
}
