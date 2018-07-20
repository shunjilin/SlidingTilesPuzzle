#include "open.hpp"
#include "closed.hpp"
#include "manhattan_distance_heuristic.hpp"
#include "tile_node.hpp"
#include "astar.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace Tiles;

using Node = TileNode<ManhattanDistanceHeuristic>;

class AStarInitialize: public testing::Test {
public:
    std::array<char, N_TILES> initial_tiles = std::array<char, N_TILES>
        ({{1, 2, 3, 4, 0, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
                    15, 16, 17, 18, 19, 20, 21, 22, 23, 24}});
    Board initial_board = Board(initial_tiles);
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
    Node initial_node =
        Node(initial_board);
};

TEST_F(AStarInitialize, AStarReturnsCorrectPath) {
    auto astar = AStar<Node, Open<Node>, Closed<Node> >();
    auto path = astar.search(initial_node);
    EXPECT_EQ((path.end() - 1)->getG(), 4);
    ASSERT_EQ(astar.search(initial_node).size(), 5);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
