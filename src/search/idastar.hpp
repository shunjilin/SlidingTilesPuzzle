#ifndef IDASTAR_HPP
#define IDASTAR_HPP

#include <vector>
#include <limits>
#include "search.hpp"
#include <iostream>

/* Iterative Deepening A* Search */
template<typename Node, typename Heuristic>
struct IDAStar : public Search<Node> {
    Heuristic heuristic;
    int threshold;
    int min_next_threshold;
    std::vector<Node> path;

    std::vector<Node>
    search(Node initial_node) override final {

        evalH(initial_node, heuristic);
        ++Search<Node>::generated;
        threshold = getF(initial_node);

        while (true) {
            min_next_threshold = std::numeric_limits<int>::max();
            auto goal_found = dfs(initial_node);
            if (goal_found) break;
            threshold = min_next_threshold;
            std::cout << "Current f layer: " << threshold << "\n";
        }

        std::reverse(path.begin(), path.end());
        return path;
    }

    bool dfs(Node node) {

        auto f = getF(node);
        if (f <= threshold && isGoal(node)) { // optimal goal node found
            path.push_back(node);
            return true;
        }

        if (f > threshold) {
            if (f < min_next_threshold) { // potential value for next threshold
                min_next_threshold = f;
            }
            return false; // threshold exceeded
        }
        
        auto child_nodes = getChildNodes(node);
        ++Search<Node>::expanded;
        for (auto child_node : child_nodes) {
            if (child_node.has_value()) {
                ++Search<Node>::generated;
                evalH(*child_node, heuristic);
                bool goal_found = dfs(*child_node);
                if (goal_found) {
                    path.push_back(node);
                    return true;
                }
                
            }
        }
        return false;
    }

    std::ostream& print(std::ostream& os) const override final {
        return os;
    }
};

#endif
