#ifndef ASTAR_HPP
#define ASTAR_HPP

#include <memory>
#include <vector>

template <typename Node, typename Heuristic, typename Open, typename Closed>
struct AStar {

    Open open;
    Closed closed;
    Heuristic const heuristic;

    // perform astar search: lazy with reopenings
    // return path to solution
    std::vector<Node>
    search(Node initial_node) {

        evalH(initial_node, heuristic);
        open.push(std::move(initial_node));

        while (!open.empty()) {
            auto node = open.pop();
            if (closed.insert(node)) {
                // check goal node
                if (isGoal(node)) {
                    return closed.getPath(node);
                }
                auto child_nodes = getChildNodes(node);
                for (auto child_node : child_nodes) {
                    if (child_node.has_value()) {
                        evalH(*child_node, heuristic);
                        open.push(std::move(*child_node));
                    }
                }
            }
        }
        return std::vector<Node>(); // no path found
    }
};

#endif
