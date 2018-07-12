#ifndef TILE_HEURISTIC_HPP
#define TILE_HEURISTIC_HPP

//#include "tile_dimensions.hpp"
#include "tiles.hpp"
#include <array>

namespace Tiles {
    struct Board;

    class TileHeuristic {
    public:
	
	virtual ~TileHeuristic() = default;
	
        virtual int getHeuristicValue(Board const &) = 0;
    };    
}

#endif
