//
// Created by Alex Chi on 2019-07-02.
//

#include "gtest/gtest.h"
#include "RegisterFile.hpp"


TEST(RegisterFile, ReadWrite) {
    RegisterFile r;
    r[1].write(1);
    EXPECT_EQ(r[1].read(), 0);
    r.tick();
    EXPECT_EQ(r[1].read(), 1);
}
