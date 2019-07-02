//
// Created by Alex Chi on 2019-07-01.
//

#include "gtest/gtest.h"
#include "Stage.h"

class MockStage : public Stage {
public:
    MockStage() : Stage(nullptr) {}

    bool flag = false;

    void mock_update() { flag = true; }

    Immediate dispatch(const std::string &key) override {
        return flag ? key[1] : key[0];
    }
};

TEST(Stage, ValueCache) {
    MockStage st;
    EXPECT_EQ(st.get("ab"), 'a');
    EXPECT_EQ(st.get("ab"), 'a');
    EXPECT_EQ(st.get("bc"), 'b');
    EXPECT_EQ(st.get("cd"), 'c');
    st.tick();
    st.mock_update();
    EXPECT_EQ(st.get("ab"), 'b');
    EXPECT_EQ(st.get("ab"), 'b');
    EXPECT_EQ(st.get("bc"), 'c');
    EXPECT_EQ(st.get("cd"), 'd');
}
