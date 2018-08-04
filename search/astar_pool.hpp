#ifndef ASTAR_HPP
#define ASTAR_HPP

#include <memory>
#include <vector>
#include "MemoryPool.h"

// Astar which uses memory pool for allocation of nodes
template <typename Node, typename Heuristic, typename Open, typename Closed>
struct AStar {

    Open open;
    Closed closed;
    Heuristic const heuristic;
    MemoryPool<Node> pool; // memory pool

    // perform astar search: lazy with reopenings
    // return path to solution
    std::vector<Node>
    search(Node initial_node) {
        auto initial_node_ptr = pool.newElement(initial_node);
        
        evalH(*initial_node_ptr, heuristic);
        open.push(initial_node_ptr);

        while (!open.empty()) {
            auto node_ptr = open.pop();

            if (closed.insert(node_ptr)) { // need to expand
                // check goal node
                if (isGoal(*node_ptr)) {
                    return closed.getPath(node_ptr);
                }

                auto child_nodes = getChildNodes(*node_ptr); // generate nodes
                for (auto child_node : child_nodes) {
                    // push all valid child nodes into open
                    if (child_node.has_value()) {
                        auto child_node_ptr =
                            pool.newElement(child_node.value());
                        evalH(*child_node_ptr, *node_ptr, heuristic);
                        open.push(child_node_ptr);
                    }
                }
            } else {
                pool.deleteElement(node_ptr); // duplicate in closed, deallocate
            }
        }
        return std::vector<Node>(); // no path found
    }
};

#endif
