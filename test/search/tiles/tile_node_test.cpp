#include "tile_node.hpp"
#include "tiles.hpp"
#include <string>
#include <sstream>
#include <gmock/gmock.h>
#include <gtest/gtest.h>


using namespace Tiles;

// dummy heuristic function
template<int WIDTH, int HEIGHT>
struct DummyHeuristic {

    int getH(Board<WIDTH, HEIGHT> const & board) const {
        return 0;
    }
    
};

class FifteenPuzzleNode: public testing::Test {
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

    TileNode<WIDTH, HEIGHT, DummyHeuristic<WIDTH, HEIGHT> > node =
        TileNode<WIDTH, HEIGHT, DummyHeuristic<WIDTH, HEIGHT> >(board);
};

TEST_F(FifteenPuzzleNode, InitializeTileNode) {
    ASSERT_THAT(node.board.tiles,
                testing::ElementsAre(1, 2, 3, 7,
                                     4, 5, 6, 0,
                                     8, 9, 10, 11,
                                     12, 13, 14, 15));
}

TEST_F(FifteenPuzzleNode, GetCost) {
    ASSERT_EQ(node.getG(), 0);
}

TEST_F(FifteenPuzzleNode, GetHeuristicValue) {
    ASSERT_EQ(node.getH(), 0);
}

TEST_F(FifteenPuzzleNode, GetChildNodes) {
    auto child_nodes = node.getChildNodes();

    EXPECT_THAT(child_nodes[UP]->board.tiles,
                testing::ElementsAre(1, 2, 3, 0,
                                     4, 5, 6, 7,
                                     8, 9, 10, 11,
                                     12, 13, 14, 15));

    EXPECT_THAT(child_nodes[DOWN]->board.tiles,
                testing::ElementsAre(1, 2, 3, 7,
                                     4, 5, 6, 11,
                                     8, 9, 10, 0,
                                     12, 13, 14, 15));

    EXPECT_THAT(child_nodes[LEFT]->board.tiles,
                testing::ElementsAre(1, 2, 3, 7,
                                     4, 5, 0, 6,
                                     8, 9, 10, 11,
                                     12, 13, 14, 15));
            
    EXPECT_FALSE(child_nodes[RIGHT].has_value());
}

TEST_F(FifteenPuzzleNode, ChildNodesIncreaseCost) {
    auto child_nodes = node.getChildNodes();
    ASSERT_EQ(child_nodes[DOWN]->getG(), node.getG() + 1);
}

TEST_F(FifteenPuzzleNode, CachePreviousMove) {
    auto child_nodes = node.getChildNodes();

    ASSERT_EQ(child_nodes[DOWN]->prev_move, DOWN);
}

TEST_F(FifteenPuzzleNode, DoNotRegenerateParentNode) {
    auto child_nodes = node.getChildNodes();
    auto grandchild_nodes = child_nodes[DOWN]->getChildNodes();
    ASSERT_FALSE(grandchild_nodes[UP].has_value());
}

TEST_F(FifteenPuzzleNode, GetParentNode) {
    auto child_node = *node.getChildNodes()[DOWN];
    ASSERT_EQ(*child_node.getParent(), node);
}

TEST_F(FifteenPuzzleNode, Node19Bytes) {
    ASSERT_EQ(sizeof(node), 19);
}


class TwentyFourPuzzleNode: public testing::Test {
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

    TileNode<WIDTH, HEIGHT, DummyHeuristic<WIDTH, HEIGHT> > node =
        TileNode<WIDTH, HEIGHT, DummyHeuristic<WIDTH, HEIGHT> >(board);
};

TEST_F(TwentyFourPuzzleNode, InitializeTileNode) {
    ASSERT_THAT(node.board.tiles,
                testing::ElementsAre(1, 2, 3, 4, 0,
                                     5, 6, 7, 8, 9,
                                     10, 11, 12, 13, 14,
                                     15, 16, 17, 18, 19,
                                     20, 21, 22, 23, 24));
}

TEST_F(TwentyFourPuzzleNode, GetCost) {
    ASSERT_EQ(node.getG(), 0);
}

TEST_F(TwentyFourPuzzleNode, GetHeuristicValue) {
    ASSERT_EQ(node.getH(), 0);
}

TEST_F(TwentyFourPuzzleNode, GetChildNodes) {
    auto child_nodes = node.getChildNodes();
    
    EXPECT_FALSE(child_nodes[UP].has_value());

    EXPECT_THAT(child_nodes[DOWN]->board.tiles,
                testing::ElementsAre(1, 2, 3, 4, 9,
                                     5, 6, 7, 8, 0,
                                     10, 11, 12, 13, 14,
                                     15, 16, 17, 18, 19,
                                     20, 21, 22, 23, 24));

    EXPECT_THAT(child_nodes[LEFT]->board.tiles,
                testing::ElementsAre(1, 2, 3, 0, 4,
                                     5, 6, 7, 8, 9,
                                     10, 11, 12, 13, 14,
                                     15, 16, 17, 18, 19,
                                     20, 21, 22, 23, 24));
            
    EXPECT_FALSE(child_nodes[RIGHT].has_value());
}

TEST_F(TwentyFourPuzzleNode, ChildNodesIncreaseCost) {
    auto child_nodes = node.getChildNodes();
    ASSERT_EQ(child_nodes[DOWN]->getG(), node.getG() + 1);
}

TEST_F(TwentyFourPuzzleNode, CachePreviousMove) {
    auto child_nodes = node.getChildNodes();

    ASSERT_EQ(child_nodes[DOWN]->prev_move, DOWN);
}

TEST_F(TwentyFourPuzzleNode, DoNotRegenerateParentNode) {
    auto child_nodes = node.getChildNodes();
    auto grandchild_nodes = child_nodes[DOWN]->getChildNodes();
    ASSERT_FALSE(grandchild_nodes[UP].has_value());
}

TEST_F(TwentyFourPuzzleNode, GetParentNode) {
    auto child_node = *node.getChildNodes()[DOWN];
    ASSERT_EQ(*child_node.getParent(), node);
}

TEST_F(TwentyFourPuzzleNode, Node28Bytes) {
    ASSERT_EQ(sizeof(node), 28);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
