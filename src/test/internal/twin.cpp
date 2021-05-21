// Copyright © 2021 Giorgio Audrito. All Rights Reserved.

#include "gtest/gtest.h"

#include "lib/internal/twin.hpp"

using namespace fcpp;


class TwinTest : public ::testing::Test {
  protected:
    virtual void SetUp() {
    }

    internal::twin<int, true> mirrored;
    internal::twin<int, false> separate;
};


TEST_F(TwinTest, TrueOperators) {
    internal::twin<int, true> x(mirrored), y{}, z;
    z = y;
    y = x;
    z = std::move(y);
    EXPECT_EQ(mirrored, z);
}

TEST_F(TwinTest, FalseOperators) {
    internal::twin<int, false> x(separate), y{}, z;
    z = y;
    y = x;
    z = std::move(y);
    EXPECT_EQ(separate, z);
}

TEST_F(TwinTest, Mirrored) {
    mirrored.first() = 42;
    EXPECT_EQ(42, mirrored.second());
    mirrored.second() = 17;
    EXPECT_EQ(17, mirrored.first());
}

TEST_F(TwinTest, Separate) {
    separate.first() = 42;
    separate.second() = 17;
    EXPECT_EQ(42, separate.first());
    EXPECT_EQ(17, separate.second());
}
