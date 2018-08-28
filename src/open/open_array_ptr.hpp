#ifndef OPEN_ARRAY_PTR_HPP
#define OPEN_ARRAY_PTR_HPP

#include <array>
#include <vector>
#include <memory>

/* Array-based Open list that allows 3 level tie-breaking [min f, max g, LIFO]
 * Store pointers instead of nodes; memory allocation is handled by client,
 * e.g. using a memory pool
 */

template <typename Node, int MAX_MOVES>
struct OpenArrayPtr {

    int min_f = MAX_MOVES;
    int max_g = -1;

    size_t size = 0;

    // index by f_value, then g_value
    std::array< std::array< std::vector<Node *>, MAX_MOVES>, MAX_MOVES> queue;

    // updates min_f to be minimum f value, updates g as well (see updateG())
    void updateFG() noexcept {
        while (min_f < MAX_MOVES) {
            updateG();
            if (max_g >= 0) return; // nodes found in g bucket
            // no node found on current f
            ++min_f;
            max_g = MAX_MOVES - 1;
        }
    }

    // updates max_g to be maximum g value in current min_f layer
    void updateG() noexcept {
        if (max_g == MAX_MOVES) --max_g; // avoid out of bounds
        while (max_g >= 0 && queue[min_f][max_g].empty()) {
            // the following line is for when memory is scarce
            //std::vector<Node *>().swap(queue[min_f][max_g]); // deallocate
            --max_g;
        }
    }

    // inserts node into open list
    void push(Node * node_ptr) {
        auto f = getF(*node_ptr);
        auto g = getG(*node_ptr);
        // inconsistent heuristic, lower f value
        if (f < min_f) {
            min_f = f;
            max_g = g;
        }
        // same f, higher g value
        else if (f == min_f && g > max_g) {
            max_g = g;
        }
        ++size;
        queue[f][g].emplace_back(node_ptr);
    }

    // pops and returns node from open list
    Node * pop() {
        if (size == 0) return nullptr;
        if (queue[min_f][max_g].empty()) updateFG();
        auto node_ptr = queue[min_f][max_g].back();
        queue[min_f][max_g].pop_back();
        --size;
        return node_ptr;
    }

    // returns true if queue is empty, also updates f and g
    bool empty() noexcept {
        if (size == 0) return true;
        return false;
    }
};

#endif
