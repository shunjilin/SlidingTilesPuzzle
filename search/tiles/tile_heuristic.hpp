#ifndef TILE_HEURISTIC_HPP
#define TILE_HEURISTIC_HPP

//#include "tile_dimensions.hpp"
#include "tiles.hpp"
#include <array>

namespace Tiles {
    struct Board;

    class TileHeuristic {
    public:
        virtual int getHeuristicValue(Board const &) = 0;
    };

    class ManhattanDistanceHeuristic : public TileHeuristic {
    private:
        // 2-D array for calculating each tile's manhattan distance
        std::array< std::array<int, N_TILES>, N_TILES> table;
    public:
        ManhattanDistanceHeuristic();
        
        int getHeuristicValue(Board const & board) override final;
    };
    
}

#endif
