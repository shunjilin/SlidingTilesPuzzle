#include "manhattan_distance.hpp"
#include <gtest/gtest.h>

int const WIDTH = 5;
int const HEIGHT = 5;

TEST(ManhattanHeuristic, correctManhattanDistance) {
    EXPECT_EQ(ManhattanDistance(0, 24, WIDTH, HEIGHT), 8);
    EXPECT_EQ(ManhattanDistance(24, 0, WIDTH, HEIGHT), 8);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
