//
// Created by Alex Chi on 2019-07-01.
//

#include "gtest/gtest.h"
#include "Stage.hpp"

class MockStage : public Stage {
public:
    MockStage() : Stage(nullptr) {}

    bool flag = false;

    void mock_update() { flag = true; }

    Immediate dispatch(Wire wire) override {
        return flag ? wire / 10 : wire % 10;
    }
};

TEST(Stage, ValueCache) {
    MockStage st;
    EXPECT_EQ(st.get(2), 2);
    EXPECT_EQ(st.get(3), 3);
    EXPECT_EQ(st.get(4), 4);
    EXPECT_EQ(st.get(5), 5);
    st.tick();
    st.mock_update();
    EXPECT_EQ(st.get(2), 0);
    EXPECT_EQ(st.get(3), 0);
    EXPECT_EQ(st.get(4), 0);
    EXPECT_EQ(st.get(5), 0);
}
