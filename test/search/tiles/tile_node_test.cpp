#include "tile_node.hpp"
#include "tiles.hpp"
#include <string>
#include <sstream>
#include <gmock/gmock.h>
#include <gtest/gtest.h>


using namespace Tiles;

// dummy heuristic function
struct DummyHeuristic {

    int getH(Board const & board) const {
        return 0;
    }
    
};

class TileNodeInitialize: public testing::Test {
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

    TileNode<DummyHeuristic> node = TileNode<DummyHeuristic>(board);
};

TEST_F(TileNodeInitialize, InitializeTileNode) {
    std::ostringstream oss;
    oss << node.board;
    ASSERT_EQ(oss.str(), "1 2 3 4 0 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 ");
}

TEST_F(TileNodeInitialize, GetCost) {
    ASSERT_EQ(node.getG(), 0);
}

TEST_F(TileNodeInitialize, GetHeuristicValue) {
    ASSERT_EQ(node.getH(), 0);
}

TEST_F(TileNodeInitialize, GetChildNodes) {
    auto child_nodes = node.getChildNodes();
    
    EXPECT_FALSE(child_nodes[UP].has_value());

    std::ostringstream oss_down;
    oss_down << (*child_nodes[DOWN]).board;
    ASSERT_EQ(oss_down.str(),  "1 2 3 4 9 5 6 7 8 0 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 ");

    std::ostringstream oss_left;
    oss_left << (*child_nodes[LEFT]).board;
    ASSERT_EQ(oss_left.str(),  "1 2 3 0 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 ");

    EXPECT_FALSE(child_nodes[RIGHT].has_value());
}

TEST_F(TileNodeInitialize, ChildNodesIncreaseCost) {
    auto child_nodes = node.getChildNodes();
    ASSERT_EQ(child_nodes[DOWN]->getG(), node.getG() + 1);
}

TEST_F(TileNodeInitialize, CachePreviousMove) {
    auto child_nodes = node.getChildNodes();

    ASSERT_EQ(child_nodes[DOWN]->prev_move, DOWN);
}

TEST_F(TileNodeInitialize, DoNotRegenerateParentNode) {
    auto child_nodes = node.getChildNodes();
    auto grandchild_nodes = child_nodes[DOWN]->getChildNodes();
    ASSERT_FALSE(grandchild_nodes[UP].has_value());
}

TEST_F(TileNodeInitialize, GetParentNode) {
    auto child_node = *node.getChildNodes()[DOWN];
    ASSERT_EQ(*child_node.getParent(), node);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
