#ifndef TILES_HPP
#define TILES_HPP

#include "tile_dimensions.hpp"
#include <vector>
#include <array>
#include <memory>
#include <limits>
#include <iostream>
#include <optional>

namespace Tiles {

    struct Board {
        // tile values, indexed as follows:
        /* 0  1  2  3  4 
           5  6  7  8  9
           10 11 12 13 14
           15 16 17 18 19
           20 21 22 23 24 */
        std::array<char, N_TILES> tiles;

        char blank_idx = std::numeric_limits<char>::max();

        Board(std::array<char, N_TILES> tiles);

	friend std::ostream& operator<<(std::ostream& os, Board const & board);
    };

    // get index of current blank tile
    char getBlankIdx(Board const & board);

    // get board from new blank index
    Board getBoardFromBlank(Board const & board, char new_blank_idx);

    // board actions
    std::optional<Board> moveBlankUp(Board const& board);
    std::optional<Board> moveBlankDown(Board const& board);
    std::optional<Board> moveBlankLeft(Board const& board);
    std::optional<Board> moveBlankRight(Board const& board);
}

//#include "tiles.cpp"

#endif
