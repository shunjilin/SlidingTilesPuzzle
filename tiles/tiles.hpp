#ifndef TILES_HPP
#define TILES_HPP

#include <vector>
#include <initializer_list>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <array>
#include <string>

namespace Tiles {

    constexpr int WIDTH = 5, HEIGHT = 5, N_TILES = WIDTH * HEIGHT;

    struct Board {
        // TODO: consider using more compact representation for this,
        // e.g. through a custom class that supports indexing
        std::array<char, N_TILES> tiles;
        char cur_blank_idx = -1;
        char prev_blank_idx = -1;       

        Board(const std::array<char, N_TILES>& tiles_list);
        
        friend std::ostream &operator<<(std::ostream& os, const Board& board); 
    };

    // direction that the blank tile moves to get new blank tile position
    enum class DIRECTION { UP, DOWN, LEFT, RIGHT, COUNT };

    // free functions to manipulate the board
    
    // TODO: consider just caching this
    // get index of current blank tile
    char getBlankIdx(const Board& board);

    // get possible new blank indexes
    std::array<char, static_cast<int>(DIRECTION::COUNT)>
                                       getNewBlankIdxs(const Board& board);

    // swap blank tile with new blank tile to get new board configuration
    Board getNewBoard(const Board& board, char newBlankIdx);
}

#endif
