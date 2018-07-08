#include "astar.hpp"
#include "heuristics.hpp"
#include <memory>
#include <vector>


std::vector<Node *>
AStar::search(Node const & initial_board,
              std::unique_ptr<Heuristic> heuristic) {
    // TODO: temporarily implement blind search
    return std::vector<Node *>();
    
} 
