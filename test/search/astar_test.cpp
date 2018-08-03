#include "open.hpp"
#include "closed.hpp"
#include "manhattan_distance_heuristic.hpp"
#include "tile_node.hpp"
#include "astar.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace Tiles;

int const WIDTH = 5;
int const HEIGHT = 5;
int const N_TILES = WIDTH*HEIGHT;

using Node = TileNode<WIDTH, HEIGHT>;
using Heuristic = ManhattanDistanceHeuristic<WIDTH, HEIGHT>;

class AStarInitialize: public testing::Test {
public:
    std::array<uint8_t, N_TILES> initial_board = std::array<uint8_t, N_TILES>
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
    Node initial_node =
        Node(initial_board);
    Heuristic heuristic = Heuristic();

    AStar<Node, Heuristic, Open<Node>, Closed<Node> > astar =
        AStar<Node, Heuristic, Open<Node>, Closed<Node> >();
};

TEST_F(AStarInitialize, AStarReturnsCorrectPath) {
    auto path = astar.search(initial_node);
    EXPECT_EQ(getG(*(path.end() - 1)), 4);
    EXPECT_EQ(getH(*(path.begin())), 4);
    EXPECT_EQ(getH(*(path.end() - 1)), 0);
    ASSERT_EQ(path.size(), 5);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
