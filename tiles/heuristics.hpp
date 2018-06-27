#ifndef HEURISTICS_HPP
#define HEURISTICS_HPP

#include "tiles.hpp"

namespace Tiles {

    struct Heuristic {
        virtual int getHeuristicValue(const Board& board) = 0;
    };

    struct ManhattanDistance : Heuristic {
        int getHeuristicValue(const Board& board) override final {
            return 0;
        }
    };

        
}

#endif
