#include "heuristics.hpp"
#include "manhattan_distance.hpp"
#include "tiles.hpp"

namespace Tiles {

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
    
    int ManhattanDistanceHeuristic::getHeuristicValue(const Board& board) {
        int heuristic_value = 0;
        for (int idx = 0; idx < N_TILES; ++idx) {
            heuristic_value += table[board.tiles[idx]][idx];
        }
        return heuristic_value;
    }
}
