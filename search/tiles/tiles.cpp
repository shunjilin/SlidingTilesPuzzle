#include "tiles.hpp"
#include "manhattan_distance_heuristic.hpp"
#include <algorithm>
#include <memory>
#include <limits>
#include <iostream>
#include <optional>

namespace Tiles {

    // constructor for board
    Board::Board(std::array<char, N_TILES> tiles) :
        tiles(std::move(tiles)) {
	blank_idx = getBlankIdx(*this);
    }

    bool Board::operator==(Board const & rhs) const {
        return tiles == rhs.tiles;
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
    Board getBoardFromBlank(Board const & board,
                            char new_blank_idx) {
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

    std::optional<Board> moveBlankUp(Board const& board) {
        if (board.blank_idx >= WIDTH) {
	    return getBoardFromBlank(board, board.blank_idx - WIDTH);
	}
	return {};
    }
    
    template<>
    std::optional<Board> moveBlank<UP>(Board const& board) {
        if (board.blank_idx >= WIDTH) {
            return getBoardFromBlank(board, board.blank_idx - WIDTH);
        }
        return {};
    }


    template<>
    std::optional<Board> moveBlank<DOWN>(Board const& board) {
        if (board.blank_idx < (WIDTH * (HEIGHT - 1))) {
            return getBoardFromBlank(board, board.blank_idx + WIDTH);
        }
        return {};
    }


    template<>
    std::optional<Board> moveBlank<LEFT>(Board const& board) { 
        if ((board.blank_idx % WIDTH) != 0) {
            return getBoardFromBlank(board, board.blank_idx - 1);
        }
        return {};
    }


    template<>
    std::optional<Board> moveBlank<RIGHT>(Board const& board) { 
        if ((board.blank_idx % WIDTH) != (WIDTH - 1)) {
            return getBoardFromBlank(board, board.blank_idx + 1);
        }
        return {};
    }
    
}

namespace std {
    size_t hash<Tiles::Board>::operator() (const Tiles::Board& board) const {
        size_t result = 0;
        for (auto i = 0; i < Tiles::N_TILES; ++i) {
            result = result * 31 + hash<int>()(board.tiles[i]);
        }
        return result;
    }
}
