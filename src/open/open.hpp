#ifndef OPEN_HPP
#define OPEN_HPP

#include <queue>
#include <vector>

/* Minimal Open List Implementation */

template <typename Node>
struct Open {

    // priority determined by node with lowest f value
    struct Compare {
        int operator()(Node const & lhs, Node const & rhs) const
            noexcept(noexcept(getF(lhs))) {          
            return getF(lhs) > getF(rhs);
        }  
    } compare;

    std::priority_queue<Node, std::vector<Node>, decltype(compare)> queue;

    // inserts node into open list
    void push(Node node) {
        queue.emplace(std::move(node));
    }

    // pops and returns node from open list
    Node pop() {
        auto node = queue.top();
        queue.pop();
        return node;
    }

    // returns true if open list is empty
    bool empty() const noexcept {
        return queue.empty();
    }
};


#endif
