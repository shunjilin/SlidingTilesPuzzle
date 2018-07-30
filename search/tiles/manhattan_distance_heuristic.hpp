#ifndef MANHATTAN_DISTANCE_HEURISTIC_HPP
#define MANHATTAN_DISTANCE_HEURISTIC_HPP

#include "tiles.hpp"
#include <cstdlib>
#include <array>

namespace Tiles {
    
    // calculate row index from index in grid of given width
    int getRowIdx(int index, int height) {
	return index / height;
    }

    // calculate row index from index in grid of given height
    int getColIdx(int index, int width) {
	return index % width;
    }

    // calculate Manhattan distance between two indexes in a grid of dimensions
    // width and height
    int manhattanDistance(char index1, char index2, int width, int height) {
	return abs(getRowIdx(index1, height) - getRowIdx(index2, height)) +
	    abs(getColIdx(index1, width) - getColIdx(index2, width));
    }

    template<int WIDTH, int HEIGHT>
    class ManhattanDistanceHeuristic {
    private:
        // 2-D array for calculating each tile's manhattan distance
        std::array< std::array<int, WIDTH*HEIGHT>, WIDTH*HEIGHT> table;
    public:
        ManhattanDistanceHeuristic() {
            // initialize lookup table
       
            // value of 0 for blank tile
            table[0].fill(0);
        
            for (int tile = 1; tile < WIDTH*HEIGHT; ++tile) {
                for (int idx = 0; idx < WIDTH*HEIGHT; ++idx) {
                    table[tile][idx] = manhattanDistance(tile, idx, WIDTH, HEIGHT);
                }
            }  
            
        }
        
        int getH(Board<WIDTH, HEIGHT> const & board) {
            int heuristic_value = 0;
            for (int idx = 0; idx < WIDTH*HEIGHT; ++idx) {
                heuristic_value += table[board.tiles[idx]][idx];
            }
            return heuristic_value;     
        }
    };
}

#endif
