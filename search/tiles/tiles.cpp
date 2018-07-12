#include "tiles.hpp"
#include "manhattan_distance_heuristic.hpp"
#include <algorithm>
#include <memory>
#include <limits>
#include <iostream>

namespace Tiles {

    // constructor for board
    Board::Board(std::array<char, N_TILES> tiles) :
        tiles(std::move(tiles)) {
	blank_idx = getBlankIdx(*this);
    }

    // get index of current blank tile
    char getBlankIdx(const Board& board) {
        if (board.blank_idx != std::numeric_limits<char>::max())
	    return board.blank_idx; // cached
        // if not cached, linear scan
        auto blank_iter = std::find(board.tiles.begin(), board.tiles.end(), 0);
        return std::distance(board.tiles.begin(), blank_iter);
    }

    // swap blank tile with new blank tile to get new board configuration
    Board getBoardFromBlank(Board const & board, char new_blank_idx) {
        auto new_board = board;
        // move blank tile
        std::swap(new_board.tiles[board.blank_idx],
                  new_board.tiles[new_blank_idx]);
        new_board.blank_idx = new_blank_idx;
        return new_board;
    }

    std::ostream& operator<<(std::ostream& os, Board const & board) {
	for (int tile : board.tiles) {
	    os << tile << " ";
	}
	return os;
    }
};
