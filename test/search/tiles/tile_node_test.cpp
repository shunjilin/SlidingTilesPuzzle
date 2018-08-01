#include "tile_node.hpp"
#include <string>
#include <sstream>
#include <gmock/gmock.h>
#include <gtest/gtest.h>


using namespace Tiles;

class FifteenPuzzleNode: public testing::Test {
public:

    static int const WIDTH = 4;
    static int const HEIGHT = 4;
    static int const N_TILES = WIDTH*HEIGHT;
    
    std::array<char, N_TILES> initial_board = std::array<char, N_TILES>
        ({{1, 2, 3, 7, 4, 5, 6, 0, 8, 9, 10, 11, 12, 13, 14, 15}});
    
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

    TileNode<WIDTH, HEIGHT> node =
        TileNode<WIDTH, HEIGHT>(initial_board);
};

TEST_F(FifteenPuzzleNode, InitializeTileNode) {
    ASSERT_THAT(node.board,
                testing::ElementsAre(1, 2, 3, 7,
                                     4, 5, 6, 0,
                                     8, 9, 10, 11,
                                     12, 13, 14, 15));
}

TEST_F(FifteenPuzzleNode, GetCost) {
    ASSERT_EQ(getG(node), 0);
}

TEST_F(FifteenPuzzleNode, GetChildNodes) {
    auto child_nodes = getChildNodes(node);

    EXPECT_THAT(child_nodes[UP]->board,
                testing::ElementsAre(1, 2, 3, 0,
                                     4, 5, 6, 7,
                                     8, 9, 10, 11,
                                     12, 13, 14, 15));

    EXPECT_THAT(child_nodes[DOWN]->board,
                testing::ElementsAre(1, 2, 3, 7,
                                     4, 5, 6, 11,
                                     8, 9, 10, 0,
                                     12, 13, 14, 15));

    EXPECT_THAT(child_nodes[LEFT]->board,
                testing::ElementsAre(1, 2, 3, 7,
                                     4, 5, 0, 6,
                                     8, 9, 10, 11,
                                     12, 13, 14, 15));
            
    EXPECT_FALSE(child_nodes[RIGHT].has_value());
}

TEST_F(FifteenPuzzleNode, ChildNodesIncreaseCost) {
    auto child_nodes = getChildNodes(node);
    ASSERT_EQ(getG(*child_nodes[DOWN]), getG(node) + 1);
}

TEST_F(FifteenPuzzleNode, CachePreviousMove) {
    auto child_nodes = getChildNodes(node);

    ASSERT_EQ(child_nodes[DOWN]->prev_move, DOWN);
}

TEST_F(FifteenPuzzleNode, DoNotRegenerateParentNode) {
    auto child_nodes = getChildNodes(node);
    auto grandchild_nodes = getChildNodes(*child_nodes[DOWN]);
    ASSERT_FALSE(grandchild_nodes[UP].has_value());
}

TEST_F(FifteenPuzzleNode, GetParentNode) {
    auto child_node = getChildNodes(node)[DOWN];
    ASSERT_EQ(getParent(*child_node), node);
}

TEST_F(FifteenPuzzleNode, Node20Bytes) {
    ASSERT_EQ(sizeof(node), 20);
}


class TwentyFourPuzzleNode: public testing::Test {
public:

    static int const WIDTH = 5;
    static int const HEIGHT = 5;
    static int const N_TILES = WIDTH*HEIGHT;
    
    std::array<char, N_TILES> initial_board = std::array<char, N_TILES>
        ({{1, 2, 3, 4, 0, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
           15, 16, 17, 18, 19, 20, 21, 22, 23, 24}});
    
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

    TileNode<WIDTH, HEIGHT> node =
        TileNode<WIDTH, HEIGHT>(initial_board);
};

TEST_F(TwentyFourPuzzleNode, InitializeTileNode) {
    ASSERT_THAT(node.board,
                testing::ElementsAre(1, 2, 3, 4, 0,
                                     5, 6, 7, 8, 9,
                                     10, 11, 12, 13, 14,
                                     15, 16, 17, 18, 19,
                                     20, 21, 22, 23, 24));
}

TEST_F(TwentyFourPuzzleNode, GetCost) {
    ASSERT_EQ(getG(node), 0);
}

TEST_F(TwentyFourPuzzleNode, GetChildNodes) {
    auto child_nodes = getChildNodes(node);
    
    EXPECT_FALSE(child_nodes[UP].has_value());

    EXPECT_THAT(child_nodes[DOWN]->board,
                testing::ElementsAre(1, 2, 3, 4, 9,
                                     5, 6, 7, 8, 0,
                                     10, 11, 12, 13, 14,
                                     15, 16, 17, 18, 19,
                                     20, 21, 22, 23, 24));

    EXPECT_THAT(child_nodes[LEFT]->board,
                testing::ElementsAre(1, 2, 3, 0, 4,
                                     5, 6, 7, 8, 9,
                                     10, 11, 12, 13, 14,
                                     15, 16, 17, 18, 19,
                                     20, 21, 22, 23, 24));
            
    EXPECT_FALSE(child_nodes[RIGHT].has_value());
}

TEST_F(TwentyFourPuzzleNode, ChildNodesIncreaseCost) {
    auto child_nodes = getChildNodes(node);
    ASSERT_EQ(getG(*child_nodes[DOWN]), getG(node) + 1);
}

TEST_F(TwentyFourPuzzleNode, CachePreviousMove) {
    auto child_nodes = getChildNodes(node);
    ASSERT_EQ(child_nodes[DOWN]->prev_move, DOWN);
}

TEST_F(TwentyFourPuzzleNode, DoNotRegenerateParentNode) {
    auto child_nodes = getChildNodes(node);
    auto grandchild_nodes = getChildNodes(*child_nodes[DOWN]);
    ASSERT_FALSE(grandchild_nodes[UP].has_value());
}

TEST_F(TwentyFourPuzzleNode, GetParentNode) {
    auto child_node = getChildNodes(node)[DOWN];
    ASSERT_EQ(getParent(*child_node), node);
}

TEST_F(TwentyFourPuzzleNode, Node29Bytes) {
    ASSERT_EQ(sizeof(node), 29);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
