#ifndef HEURISTICS_HPP
#define HEURISTICS_HPP

#include "tiles.hpp"
#include <array>

namespace Tiles {

    class Heuristic {
    public:
        virtual int getHeuristicValue(const Board& board) = 0;
    };

    class ManhattanDistanceHeuristic : Heuristic {
    private:
        // 2-D array for calculating each tile's manhattan distance
        std::array< std::array<int, N_TILES>, N_TILES> table;
    public:
        ManhattanDistanceHeuristic();
        
        int getHeuristicValue(const Board& board) override final;
    };
}

#endif
