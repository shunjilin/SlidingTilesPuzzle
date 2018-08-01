#ifndef MANHATTAN_DISTANCE_HEURISTIC_HPP
#define MANHATTAN_DISTANCE_HEURISTIC_HPP

#include <cstdlib>
#include <array>
#include "tile_node.hpp"

namespace Tiles {
    
    // calculate row index from index in grid of given width
    int getRowIdx(int index, int width) {
	return index / width;
    }

    // calculate col index from index in grid of given width
    int getColIdx(int index, int width) {
	return index % width;
    }

    // calculate Manhattan distance between two indexes in a grid of given width
    int manhattanDistance(char index1, char index2, int width) {
	return abs(getRowIdx(index1, width) - getRowIdx(index2, width)) +
	    abs(getColIdx(index1, width) - getColIdx(index2, width));
    }

    template<int WIDTH, int HEIGHT>
    struct ManhattanDistanceHeuristic {
        // 2-D array for calculating each tile's manhattan distance
        std::array< std::array<int, WIDTH*HEIGHT>, WIDTH*HEIGHT> table;
        
        ManhattanDistanceHeuristic() {
            // initialize lookup table
            
            // value of 0 for blank tile
            table[0].fill(0);
            
            for (int tile = 1; tile < WIDTH*HEIGHT; ++tile) {
                for (int idx = 0; idx < WIDTH*HEIGHT; ++idx) {
                    table[tile][idx] = manhattanDistance(tile, idx, WIDTH);
                }
            }
        }
    };

    template<int WIDTH, int HEIGHT, typename Heuristic>
    void evalH(TileNode<WIDTH, HEIGHT> & node, Heuristic const & heuristic) {
        int heuristic_value = 0;
        for (int idx = 0; idx < WIDTH*HEIGHT; ++idx) {
            heuristic_value += heuristic.table[node.board[idx]][idx];
        }
        node.h_val = heuristic_value;
    }
}

#endif
