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
        std::vector<char> tiles;

        Board(std::initializer_list<char> tiles_list) :
            tiles(tiles_list) {}
        
        friend std::ostream &operator<<(std::ostream& os, const Board& board); 
    };

    // free functions to manipulate the board
    
    // TODO: consider just caching this
    // get index of current blank tile
    char getBlankIdx(const Board& board);

    // get possible new blank indexes
    std::vector<char> getNewBlankIdxs(const Board& board);

    // swap blank tile with new blank tile to get new board configuration
    Board getNewBoard(const Board& board, char newBlankIdx);
}

#endif
