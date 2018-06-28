#include "astar.hpp"
#include "tiles.hpp"
#include "heuristics.hpp"
#include <memory>
#include <vector>


std::vector<Tiles::Board>
AStar::search(Tiles::Board const& initial_board,
              std::unique_ptr<Tiles::Heuristic> heuristic) {
    // TODO: temporarily implement blind search
    return std::vector<Tiles::Board>();
    
} 
