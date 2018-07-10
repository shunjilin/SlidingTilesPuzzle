#include "manhattan_distance_heuristic.hpp"
#include <gtest/gtest.h>

using namespace Tiles;

// test manhattan distance functions
int const WIDTH = 5;
int const HEIGHT = 5;

TEST(ManhattanDistance, correctRowIdx) {
    EXPECT_EQ(getRowIdx(0, ::HEIGHT), 0);
    EXPECT_EQ(getRowIdx(6, ::HEIGHT), 1);
    EXPECT_EQ(getRowIdx(12, ::HEIGHT), 2);
    EXPECT_EQ(getRowIdx(18, ::HEIGHT), 3);
    EXPECT_EQ(getRowIdx(24, ::HEIGHT), 4);
}

TEST(ManhattanDistance, correctColIdx) {
    EXPECT_EQ(getColIdx(0, ::WIDTH), 0);
    EXPECT_EQ(getColIdx(6, ::WIDTH), 1);
    EXPECT_EQ(getColIdx(12, ::WIDTH), 2);
    EXPECT_EQ(getColIdx(18, ::WIDTH), 3);
    EXPECT_EQ(getColIdx(24, ::WIDTH), 4);
}

TEST(ManhattanDistance, correctManhattanDistance) {
    EXPECT_EQ(manhattanDistance(1, 2, ::WIDTH, ::HEIGHT), 1);
    EXPECT_EQ(manhattanDistance(0, 24, ::WIDTH, ::HEIGHT), 8);
    EXPECT_EQ(manhattanDistance(24, 0, ::WIDTH, ::HEIGHT), 8);
}

// test manhattan distance heuristic

class BoardInitialize: public testing::Test {
public:
    std::array<char, N_TILES> initial_tiles = std::array<char, N_TILES>
        ({{1, 2, 3, 4, 0, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
           15, 16, 17, 18, 19, 20, 21, 22, 23, 24}});
    
    Board board = Board(initial_tiles);
    // initial board
    /* 1  2  3  4  0
       5  6  7  8  9
       10 11 12 13 14
       15 16 17 18 19
       20 21 22 23 24 */
    
    // goal board
    /* 0  1  2  3  4
       5  6  7  8  9
       10 11 12 13 14
       15 16 17 18 19
       20 21 22 23 24 */
    ManhattanDistanceHeuristic heuristic = ManhattanDistanceHeuristic();
};

TEST_F(BoardInitialize, correctManhattanHeuristic) {
    ASSERT_EQ(heuristic.getHeuristicValue(board), 4);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
