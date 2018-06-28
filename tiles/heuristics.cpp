#include "heuristics.hpp"
#include "manhattan_distance.hpp"
#include "tiles.hpp"

namespace Tiles {

    ManhattanDistanceHeuristic::ManhattanDistanceHeuristic() {
        // initialize lookup table
        for (char tile = 1; tile < N_TILES; ++tile) {
            
        }      
    }
    
    int ManhattanDistanceHeuristic::getHeuristicValue(const Board& board) {
        return 0;
    }
}
