//
// Created by Alex Chi on 2019-07-01.
//

#include "gtest/gtest.h"
#include "Register.hpp"


TEST(Register, ReadWrite) {
    Register <unsigned> r;
    r.write(1);
    EXPECT_EQ(r.read(), 0);
    r.tick();
    EXPECT_EQ(r.read(), 1);
}
