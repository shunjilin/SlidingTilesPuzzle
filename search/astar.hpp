#ifndef ASTAR_HPP
#define ASTAR_HPP

#include <memory>
#include <vector>

template <typename Node>
struct AStar {

    // perform astar search: lazy with reopenings
    std::vector<Node>
    search(Node const & initial_node) {
	return std::vector<Node>();
    }
};

#endif
