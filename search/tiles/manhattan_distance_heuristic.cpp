#include "manhattan_distance_heuristic.hpp"
#include "tiles.hpp"
#include <cstdlib>

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
    };

    ManhattanDistanceHeuristic::ManhattanDistanceHeuristic() {
        // initialize lookup table
        
        // value of 0 for blank tile
        table[0].fill(0);
        
        for (int tile = 1; tile < N_TILES; ++tile) {
            for (int idx = 0; idx < N_TILES; ++idx) {
                table[tile][idx] = manhattanDistance(tile, idx, WIDTH, HEIGHT);
            }
        }     
    }
    
    int ManhattanDistanceHeuristic::getHeuristicValue(const Board & board) {
        int heuristic_value = 0;
        for (int idx = 0; idx < N_TILES; ++idx) {
            heuristic_value += table[board.tiles[idx]][idx];
        }
        return heuristic_value;
    }
}
