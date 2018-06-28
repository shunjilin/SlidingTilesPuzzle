#include "heuristics.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace Tiles;

TEST(ManhattanHeuristic, correctManhattanDistance) {
    ASSERT_EQ(ManhattanDistance(0, 24, WIDTH, HEIGHT), 8);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
