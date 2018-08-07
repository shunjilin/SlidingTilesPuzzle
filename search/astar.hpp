#ifndef ASTAR_HPP
#define ASTAR_HPP

#include <memory>
#include <vector>
#include "search.hpp"
#include "open_array.hpp"
#include "closed_open_address.hpp"

template <typename Node, typename Heuristic, size_t ClosedEntries = 512927357 >
struct AStar : public Search<Node> {

    Heuristic heuristic;
    OpenArray<Node> open;
    ClosedOpenAddress<Node, ClosedEntries> closed;

    // perform astar search: lazy with reopenings
    // return path to solution
    std::vector<Node>
    search(Node initial_node) override final {

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
