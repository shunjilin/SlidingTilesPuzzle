#ifndef TILES_HPP
#define TILES_HPP

#include <vector>
#include <array>
#include <memory>
#include <limits>
#include <iostream>
#include <optional>

namespace Tiles {

    // board dimensions
    constexpr int WIDTH = 5,
        HEIGHT = 5,
        N_TILES = WIDTH * HEIGHT,
        N_MOVES = 4;

    // board moves; blank moved in the specified direction
    enum MOVE : char {
        UP, DOWN, LEFT, RIGHT, NONE
    };

    struct Board {
        // tile values, indexed as follows:
        /* 0  1  2  3  4 
           5  6  7  8  9
           10 11 12 13 14
           15 16 17 18 19
           20 21 22 23 24 */
        
        // tile at each index
        std::array<char, N_TILES> tiles;

        // index of blank
        char blank_idx = std::numeric_limits<char>::max();

        // construct board from array of tiles
        Board(std::array<char, N_TILES> tiles);

        bool operator==(Board const & rhs) const;

        // pretty print board
	friend std::ostream& operator<<(std::ostream& os, Board const & board);
    };

    // get index of current blank tile
    char getBlankIdx(Board const & board);

    // get board from new blank index
    Board getBoardFromBlank(Board const & board, char new_blank_idx);

    // get new board from moving blank in MoveDirection
    template<MOVE MoveDirection>
    std::optional<Board> moveBlank(Board const& board);
    
}

// overload default hash
namespace std
{
    template<>
    struct hash<Tiles::Board>
    {
        size_t operator() (const Tiles::Board& board) const;
    };
}


#endif
