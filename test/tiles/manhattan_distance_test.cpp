#include "manhattan_distance.hpp"
#include <gtest/gtest.h>

int const WIDTH = 5;
int const HEIGHT = 5;

TEST(ManhattanDistance, correctRowIdx) {
    EXPECT_EQ(getRowIdx(0, HEIGHT), 0);
    EXPECT_EQ(getRowIdx(6, HEIGHT), 1);
    EXPECT_EQ(getRowIdx(12, HEIGHT), 2);
    EXPECT_EQ(getRowIdx(18, HEIGHT), 3);
    EXPECT_EQ(getRowIdx(24, HEIGHT), 4);
}

TEST(ManhattanDistance, correctColIdx) {
    EXPECT_EQ(getColIdx(0, WIDTH), 0);
    EXPECT_EQ(getColIdx(6, WIDTH), 1);
    EXPECT_EQ(getColIdx(12, WIDTH), 2);
    EXPECT_EQ(getColIdx(18, WIDTH), 3);
    EXPECT_EQ(getColIdx(24, WIDTH), 4);
}

TEST(ManhattanDistance, correctManhattanDistance) {
    EXPECT_EQ(manhattanDistance(1, 2, WIDTH, HEIGHT), 1);
    EXPECT_EQ(manhattanDistance(0, 24, WIDTH, HEIGHT), 8);
    EXPECT_EQ(manhattanDistance(24, 0, WIDTH, HEIGHT), 8);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
