#include "tiles.hpp"
#include "manhattan_distance_heuristic.hpp"
#include <gtest/gtest.h>

using namespace Tiles;

// test manhattan distance functions
int const WIDTH = 3;
int const HEIGHT = 4;
int const N_TILES = WIDTH*HEIGHT;

TEST(ManhattanDistance, correctRowIdx) {
    EXPECT_EQ(getRowIdx(0, ::WIDTH), 0);
    EXPECT_EQ(getRowIdx(4, ::WIDTH), 1);
    EXPECT_EQ(getRowIdx(8, ::WIDTH), 2);
    EXPECT_EQ(getRowIdx(10, ::WIDTH), 3);
}

TEST(ManhattanDistance, correctColIdx) {
    EXPECT_EQ(getColIdx(0, ::WIDTH), 0);
    EXPECT_EQ(getColIdx(4, ::WIDTH), 1);
    EXPECT_EQ(getColIdx(8, ::WIDTH), 2);
    EXPECT_EQ(getColIdx(10, ::WIDTH), 1);
}

TEST(ManhattanDistance, correctManhattanDistance) {
    EXPECT_EQ(manhattanDistance(1, 2, ::WIDTH), 1);
    EXPECT_EQ(manhattanDistance(0, 11, ::WIDTH), 5);
    EXPECT_EQ(manhattanDistance(11, 0, ::WIDTH), 5);
}

// test manhattan distance heuristic

class BoardInitialize: public testing::Test {
public:
    std::array<char, N_TILES> initial_tiles = std::array<char, N_TILES>
        ({{1, 2, 5, 3, 4, 0, 6, 7, 8, 9, 10, 11}});
    
    Board<WIDTH, HEIGHT> board = Board<WIDTH, HEIGHT>(initial_tiles);
    // initial board
    /* 1  2  5
       3  4  0
       6  7  8
       9  10 11 */
    
    // goal board
    /* 0  1  2
       3  4  5
       6  7  8
       9  10 11 */
    ManhattanDistanceHeuristic<WIDTH, HEIGHT> heuristic =
        ManhattanDistanceHeuristic<WIDTH, HEIGHT>();
};

TEST_F(BoardInitialize, correctManhattanHeuristic) {
    ASSERT_EQ(heuristic.getH(board), 3);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
