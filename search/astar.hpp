#ifndef ASTAR_HPP
#define ASTAR_HPP

#include "search.hpp"
#include <memory>
#include <vector>

struct AStar : Search {

    // perform astar search: lazy with reopenings
    std::vector<Node *>
    search(Node const & initial_node) override final;
};

#endif
