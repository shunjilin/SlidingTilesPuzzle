#ifndef TILES_HPP
#define TILES_HPP

#include "node.hpp"
#include <vector>
#include <array>
#include <memory>

namespace Tiles {

    constexpr int WIDTH = 5, HEIGHT = 5, N_TILES = WIDTH * HEIGHT;

    struct Board {
        // tile values, indexed as follows:
        /* 0  1  2  3  4 
           5  6  7  8  9
           10 11 12 13 14
           15 16 17 18 19
           20 21 22 23 24 */
        std::array<char, N_TILES> tiles;

        char blank_idx = -1;

        Board(std::array<char, N_TILES> tiles);
    };

    // get index of current blank tile
    char getBlankIdx(Board const & board);

    // get board from new blank index
    Board getBoardFromBlank(Board const & board, char new_blank_idx);

    struct TileNode : Node {
    
        Board board;
        // goal board configuration
        static Board goal_board;
        int cost = 0; // g-value

        // caching to regenerate parent node
        char prev_blank_idx = -1;

        TileNode(Board board, char prev_blank_idx);

        std::vector<std::unique_ptr<Node> > getChildNodes() const override final;
    };
}
#endif
