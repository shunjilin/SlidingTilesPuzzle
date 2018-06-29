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
        // tile values, indexed as follows:
        /* 0  1  2  3  4 
           5  6  7  8  9
           10 11 12 13 14
           15 16 17 18 19
           20 21 22 23 24 */
        std::array<char, N_TILES> tiles;

        char cur_blank_idx = -1;
        char prev_blank_idx = -1;       

        Board(const std::array<char, N_TILES>& tiles);
        
        friend std::ostream &operator<<(std::ostream& os, const Board& board);

        // goal board configuration
        static std::array<char, N_TILES> goal_tiles;
    };

    // direction that the blank tile moves to get new blank tile position
    enum DIRECTION { UP, DOWN, LEFT, RIGHT, COUNT };

    // free functions to manipulate the board
    
    // TODO: consider just caching this
    // get index of current blank tile
    char getBlankIdx(const Board& board);

    // get possible new blank indexes
    std::array<char, DIRECTION::COUNT>
    getNewBlankIdxs(const Board& board);

    // swap blank tile with new blank tile to get new board configuration
    Board getNewBoard(const Board& board, char newBlankIdx);
}

#endif
