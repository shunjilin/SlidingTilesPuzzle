#include "tiles.hpp"
#include <algorithm>

namespace Tiles {

    // constructor for board
    Board::Board(std::array<char, N_TILES> tiles) :
        tiles(std::move(tiles)), blank_idx(getBlankIdx(*this)) {}

    // get index of current blank tile
    char getBlankIdx(const Board& board) {
        if (board.blank_idx != -1) return board.blank_idx; // cached
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

    // constructor for tile node
    TileNode::TileNode(Board board, char prev_blank_idx) :
        board(std::move(board)) , prev_blank_idx(prev_blank_idx) {}

    // generate child nodes from current node
    std::vector<std::unique_ptr<Node> > TileNode::getChildNodes() const {
        std::vector<std::unique_ptr<Node> > child_nodes;

        // move blank up
        if (board.blank_idx >= WIDTH) {
            child_nodes.emplace_back(
                std::make_unique<TileNode>(
                TileNode(getBoardFromBlank(board, board.blank_idx - WIDTH),
                         board.blank_idx)
                    )
                );
        }
        // move blank down
        if (board.blank_idx < (WIDTH * (HEIGHT - 1))) {
            child_nodes.emplace_back(
                std::make_unique<TileNode>(
                TileNode(getBoardFromBlank(board, board.blank_idx + WIDTH),
                         board.blank_idx)
                    )
                );
        }
        // move blank left
        if ((board.blank_idx % WIDTH) != 0) {
            child_nodes.emplace_back(
                std::make_unique<TileNode>(
                TileNode(getBoardFromBlank(board, board.blank_idx - 1),
                         board.blank_idx)
                    )
                );
        }
        // move blank right
        if ((board.blank_idx % WIDTH) != (WIDTH - 1)) {
            child_nodes.emplace_back(
                std::make_unique<TileNode>(
                TileNode(getBoardFromBlank(board, board.blank_idx + 1),
                         board.blank_idx)
                    )
                );
        }
        return child_nodes;
    };

};
