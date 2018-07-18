#include "tiles.hpp"
#include <string>
#include <sstream>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace Tiles;

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
};

TEST_F(BoardInitialize, InitializeTiles) {
    std::ostringstream oss;
    oss << board;
    ASSERT_EQ(oss.str(), "1 2 3 4 0 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 ");
}

TEST_F(BoardInitialize, getBlankPosition) {
    ASSERT_EQ(getBlankIdx(board), 4);
}

TEST_F(BoardInitialize, getBoardFromNewBlank) {
    auto new_board = getBoardFromBlank(board, 3);
    std::ostringstream oss;
    oss << new_board;
    ASSERT_EQ(oss.str(), "1 2 3 0 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 ");
}

TEST_F(BoardInitialize, getBoardFromMoveBlankUp) {
    auto new_board = moveBlank<UP>(board);
    ASSERT_EQ(new_board.has_value(), false);
}

TEST_F(BoardInitialize, getBoardFromMoveBlankDown) {
    auto new_board = moveBlank<DOWN>(board);
    std::ostringstream oss;
    oss << *new_board;
    ASSERT_EQ(oss.str(), "1 2 3 4 9 5 6 7 8 0 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 ");
}

TEST_F(BoardInitialize, getBoardFromMoveBlankLeft) {
    auto new_board = moveBlank<LEFT>(board);
    std::ostringstream oss;
    oss << *new_board;
    ASSERT_EQ(oss.str(), "1 2 3 0 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 ");
}

TEST_F(BoardInitialize, getBoardFromMoveBlankRight) {
    auto new_board = moveBlank<RIGHT>(board);
    ASSERT_EQ(new_board.has_value(), false);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
