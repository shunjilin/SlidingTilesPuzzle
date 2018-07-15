#ifndef OPEN_HPP
#define OPEN_HPP

#include <queue>
#include <vector>

template <typename Node>
struct Open {

    struct Compare {
        int operator()(Node const & lhs, Node const & rhs) const {          
            return (lhs.getCost() + lhs.getHeuristicValue()) >
                (rhs.getCost() + rhs.getHeuristicValue());
        }  
    } compare;

    std::priority_queue<Node, std::vector<Node>, decltype(compare)> queue;
    
    void push(Node node) {
        queue.push(std::move(node));
    }

    Node pop() {
        auto node = queue.top();
        queue.pop();
        return node;
    }

    bool empty() const {
        return queue.empty();
    }
};


#endif
