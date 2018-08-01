#ifndef TILES_HPP
#define TILES_HPP

#include <vector>
#include <array>
#include <memory>
#include <limits>
#include <iostream>
#include <optional>
#include <iomanip>
#include <algorithm>

namespace Tiles {
    
    // board moves; blank moved in the specified direction
    enum MOVE : char {
        UP, RIGHT, LEFT, DOWN, N_MOVES, NONE // best ordering for 15 puzzle
    };

    // board of WIDTH * HEIGHT dimension
    template<int WIDTH, int HEIGHT=WIDTH>
    struct Board {
        // tile values, indexed as follows (e.g. 24 puzzle):
        /* 0  1  2  3  4 
           5  6  7  8  9
           10 11 12 13 14
           15 16 17 18 19
           20 21 22 23 24 */
        
        // tile at each index
        std::array<char, WIDTH*HEIGHT> tiles = std::array<char, WIDTH*HEIGHT>();

        // index of blank
        char blank_idx = std::numeric_limits<char>::max();
        
        // construct board from array of tiles
        Board(std::array<char, WIDTH*HEIGHT> tiles) : tiles(std::move(tiles)) {
            getBlankIdx();
        }

        bool operator==(Board<WIDTH, HEIGHT> const & rhs) const {
            return tiles == rhs.tiles;
        }

        // get index of current blank tile
        char getBlankIdx() {
            // not cached, do linear scan
            if (blank_idx == std::numeric_limits<char>::max()) {
                 auto blank_iter = std::find(tiles.begin(), tiles.end(), 0);
                 blank_idx = std::distance(tiles.begin(), blank_iter);
            }
            return blank_idx;
        }

        // swap blank tile with new blank tile to get new board configuration
        Board<WIDTH, HEIGHT> getBoardFromBlank(char new_blank_idx) const {
            auto new_board = *this;
            // move blank tile
            std::swap(new_board.tiles[blank_idx],
                      new_board.tiles[new_blank_idx]);
            new_board.blank_idx = new_blank_idx;
            return new_board;
        }

        // get new board from moving blank
        // partial template specializations for functions note allowed!
        // fall back to switch statements
        std::optional<Board<WIDTH, HEIGHT> > moveBlank(MOVE move) const {
            switch(move) {
            case UP :
                if (blank_idx >= WIDTH) {
                    return getBoardFromBlank(blank_idx - WIDTH);
                }
                break;
            case DOWN:
                if (blank_idx < (WIDTH * (HEIGHT - 1))) {
                    return getBoardFromBlank(blank_idx + WIDTH);
                }
                break;
            case LEFT:
                if ((blank_idx % WIDTH) != 0) {
                    return getBoardFromBlank(blank_idx - 1);
                }
                break;
            case RIGHT:
                if ((blank_idx % WIDTH) != (WIDTH - 1)) {
                    return getBoardFromBlank(blank_idx + 1);   
                }
                break;
            default:
                break;
            }
            return {};
        }
    };

    // pretty print board
    template<int WIDTH, int HEIGHT>
    std::ostream& operator<< (std::ostream& os,
                              Board<WIDTH, HEIGHT> const & board) {
        for (int row = 0; row < HEIGHT; ++row) {
            for (int col = 0; col < WIDTH; ++ col) {
                os << std::setw(2) <<
                    static_cast<int>(board.tiles[row * WIDTH + col]) << " ";
            }
            os << "\n";
        }
	return os;
    }
}

#endif
