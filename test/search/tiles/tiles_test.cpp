#include "tiles.hpp"
#include <string>
#include <sstream>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace Tiles;

class FifteenPuzzle: public testing::Test {
public:
    static int const WIDTH = 4;
    static int const HEIGHT = 4;
    static int const N_TILES = WIDTH*HEIGHT;
    
    std::array<char, N_TILES> initial_tiles = std::array<char, N_TILES>
        ({{1, 2, 3, 7, 4, 5, 6, 0, 8, 9, 10, 11, 12, 13, 14, 15}});
    
    Board<WIDTH, HEIGHT> board = Board<WIDTH, HEIGHT>(initial_tiles);
    // initial board
    /* 1  2  3  7
       4  5  6  0
       8  9  10 11
       12 13 14 15 */
    
    // goal board
    /* 0  1  2  3
       4  5  6  7
       8  9  10 11
       12 13 14 15 */
};

TEST_F(FifteenPuzzle, InitializeTiles) {
    ASSERT_THAT(board.tiles,
                testing::ElementsAre(1, 2, 3, 7,
                                     4, 5, 6, 0,
                                     8, 9, 10, 11,
                                     12, 13, 14, 15));
}

TEST_F(FifteenPuzzle, getBlankPosition) {
    ASSERT_EQ(board.getBlankIdx(), 7);
}

TEST_F(FifteenPuzzle, getBoardFromNewBlank) {
    auto new_board = board.getBoardFromBlank(3);
    ASSERT_THAT(new_board.tiles,
                testing::ElementsAre(1, 2, 3, 0,
                                     4, 5, 6, 7,
                                     8, 9, 10, 11,
                                     12, 13, 14, 15));
}

TEST_F(FifteenPuzzle, getBoardFromMoveBlankUp) {
    auto new_board = board.moveBlank(UP);
    ASSERT_THAT(new_board->tiles,
                testing::ElementsAre(1, 2, 3, 0,
                                     4, 5, 6, 7,
                                     8, 9, 10, 11,
                                     12, 13, 14, 15));
}

TEST_F(FifteenPuzzle, getBoardFromMoveBlankDown) {
    auto new_board = board.moveBlank(DOWN);
    ASSERT_THAT(new_board->tiles,
                testing::ElementsAre(1, 2, 3, 7,
                                     4, 5, 6, 11,
                                     8, 9, 10, 0,
                                     12, 13, 14, 15));
}

TEST_F(FifteenPuzzle, getBoardFromMoveBlankLeft) {
    auto new_board = board.moveBlank(LEFT);
    ASSERT_THAT(new_board->tiles,
                testing::ElementsAre(1, 2, 3, 7,
                                     4, 5, 0, 6,
                                     8, 9, 10, 11,
                                     12, 13, 14, 15));
}

TEST_F(FifteenPuzzle, getBoardFromMoveBlankRight) {
    auto new_board = board.moveBlank(RIGHT);
    ASSERT_EQ(new_board.has_value(), false);
}

class TwentyFourPuzzle: public testing::Test {
public:
    static int const WIDTH = 5;
    static int const HEIGHT = 5;
    static int const N_TILES = WIDTH*HEIGHT;
    
    std::array<char, N_TILES> initial_tiles = std::array<char, N_TILES>
        ({{1, 2, 3, 4, 0, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
           15, 16, 17, 18, 19, 20, 21, 22, 23, 24}});
    
    Board<WIDTH, HEIGHT> board = Board<WIDTH, HEIGHT>(initial_tiles);
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
};

TEST_F(TwentyFourPuzzle, InitializeTiles) {
    ASSERT_THAT(board.tiles,
                testing::ElementsAre(1, 2, 3, 4, 0,
                                     5, 6, 7, 8, 9,
                                     10, 11, 12, 13, 14,
                                     15, 16, 17, 18, 19,
                                     20, 21, 22, 23, 24));
}

TEST_F(TwentyFourPuzzle, getBlankPosition) {
    ASSERT_EQ(board.getBlankIdx(), 4);
}

TEST_F(TwentyFourPuzzle, getBoardFromNewBlank) {
    auto new_board = board.getBoardFromBlank(3);
    ASSERT_THAT(new_board.tiles,
                testing::ElementsAre(1, 2, 3, 0, 4,
                                     5, 6, 7, 8, 9,
                                     10, 11, 12, 13, 14,
                                     15, 16, 17, 18, 19,
                                     20, 21, 22, 23, 24));
}

TEST_F(TwentyFourPuzzle, getBoardFromMoveBlankUp) {
    auto new_board = board.moveBlank(UP);
    ASSERT_EQ(new_board.has_value(), false);
}

TEST_F(TwentyFourPuzzle, getBoardFromMoveBlankDown) {
    auto new_board = board.moveBlank(DOWN);
    ASSERT_THAT(new_board->tiles,
                testing::ElementsAre(1, 2, 3, 4, 9,
                                     5, 6, 7, 8, 0,
                                     10, 11, 12, 13, 14,
                                     15, 16, 17, 18, 19,
                                     20, 21, 22, 23, 24));
}

TEST_F(TwentyFourPuzzle, getBoardFromMoveBlankLeft) {
    auto new_board = board.moveBlank(LEFT);
    ASSERT_THAT(new_board->tiles,
                testing::ElementsAre(1, 2, 3, 0, 4,
                                     5, 6, 7, 8, 9,
                                     10, 11, 12, 13, 14,
                                     15, 16, 17, 18, 19,
                                     20, 21, 22, 23, 24));
}

TEST_F(TwentyFourPuzzle, getBoardFromMoveBlankRight) {
    auto new_board = board.moveBlank(RIGHT);
    ASSERT_EQ(new_board.has_value(), false);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
