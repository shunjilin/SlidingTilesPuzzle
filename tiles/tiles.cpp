#include "tiles.hpp"


namespace Tiles {
    
    std::ostream &operator<<(std::ostream& os, const Board& board) {
        for (auto tile : board.tiles) {
            os << std::to_string(tile) << " ";
        }
        return os;
    }

    // free functions to manipulate the board
    
    // direction that the blank tile moves to get new blank tile position
    enum class DIRECTION { UP, DOWN, LEFT, RIGHT };

    // TODO: consider reordering / shuffling
    const std::array<DIRECTION, 4> directions =
    { {DIRECTION::UP, DIRECTION::DOWN, DIRECTION::LEFT, DIRECTION::RIGHT} };
    
    // TODO: consider just caching this
    // get index of current blank tile
    char getBlankIdx(const Board& board) {
        auto blank_iter = std::find(board.tiles.begin(), board.tiles.end(), 0);
        return std::distance(board.tiles.begin(), blank_iter);
    }

    // get possible new blank indexes
    std::vector<char> getNewBlankIdxs(const Board& board) {
        auto blank_idx = getBlankIdx(board);
        std::vector<char> new_blank_idxs;
        // only accept and push valid indexes
        for (auto direction : directions) {
            if (direction == DIRECTION::UP && blank_idx >= WIDTH) {
                new_blank_idxs.push_back(blank_idx - WIDTH);
            }
            if (direction == DIRECTION::DOWN &&
                blank_idx < (WIDTH * (HEIGHT - 1))) {
                new_blank_idxs.push_back(blank_idx + WIDTH);
            }
            if (direction == DIRECTION::LEFT && (blank_idx % WIDTH) != 0) {
                new_blank_idxs.push_back(blank_idx - 1);
            }
            if (direction == DIRECTION::RIGHT &&
                (blank_idx % WIDTH) != (WIDTH - 1)) {
                new_blank_idxs.push_back(blank_idx + 1);
            }
        }
        return new_blank_idxs;
    }

    // swap blank tile with new blank tile to get new board configuration
    Board getNewBoard(const Board& board, char newBlankIdx) {
        auto new_board = board;
        auto tile_to_swap = board.tiles[newBlankIdx];
        new_board.tiles[getBlankIdx(new_board)] = tile_to_swap;
        new_board.tiles[newBlankIdx] = 0;
        return new_board;
    }
}
