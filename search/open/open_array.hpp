#ifndef OPEN_ARRAY_HPP
#define OPEN_ARRAY_HPP

#include <array>

// open list using array-based open list for 3 level tie-breaking

template <typename Node>
struct OpenArray {

    static int const MAX_MOVES = 255;

    int min_f = MAX_MOVES;
    int max_g = MAX_MOVES;

    // index by f_value, then g_value
    std::array< std::array< std::vector<Node>, MAX_MOVES>, MAX_MOVES> queue;

    // update min_f to be minimum f value, update g as well
    void updateFG() {
        while (min_f < MAX_MOVES) {
            updateG();
            if (max_g == MAX_MOVES) { ; // no nodes found on current f
                ++min_f;
            } else {
                return;
            }
        }
    }

    // update max_g to be maximum g value in current min_f layer
    void updateG() {
        if (max_g == MAX_MOVES) --max_g; // avoid out of bounds
        while (queue[min_f][max_g].empty()) {
            if (max_g == 0) { // entire f layer is empty
                max_g = MAX_MOVES; // reset
                return;
            }
            --max_g;
        }
    }

    // push node into queue
    void push(Node node) {
        auto f = getF(node);
        auto g = getG(node);
        // inconsistent heuristic, lower f value
        if (f < min_f) {
            min_f = f;
            max_g = g;
        }
        // same f, higher g value
        else if (f == min_f && g > max_g) {
            max_g = g;
        }
        queue[f][g].emplace_back(node);
    }

    // pop node
    Node pop() {
        if (queue[min_f][max_g].empty()) updateFG(); // guard in case
        auto node = queue[min_f][max_g].back();
        queue[min_f][max_g].pop_back();
        return node;
    }

    // check if queue is empty, also updates f and g
    bool empty() {
        updateFG();
        if (min_f == MAX_MOVES) return true;
        return false;
    }
};

#endif
