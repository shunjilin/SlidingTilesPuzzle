#ifndef MANHATTAN_DISTANCE_HEURISTICS_HPP
#define MANHATTAN_DISTANCE_HEURISTICS_HPP

#include "tiles.hpp"
#include "heuristics.hpp"
#include <array>

namespace Tiles {
    
    class ManhattanDistanceHeuristic : Heuristic {
    private:
        // 2-D array for calculating each tile's manhattan distance
        std::array< std::array<int, N_TILES>, N_TILES> table;
    public:
        ManhattanDistanceHeuristic();
        
        int getHeuristicValue(Node const & node) override final;
    };
}

#endif
