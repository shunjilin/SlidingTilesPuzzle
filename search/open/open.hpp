#ifndef OPEN_HPP
#define OPEN_HPP

#include <queue>
/*
template <typename Node>
auto compare = [](Node lhs, Node rhs) {
    return (lhs.getCost() + lhs.getHeuristicValue()) >
    (rhs.getCost() + rhs.getHeuristicValue());
};

template <typename Node>
struct Open {

    std::priority_queue<Node, decltype(compare<Node>)> queue;
    
    void push(Node node) {
        priority_queue.push(std::move(node));
    }

    Node pop() {
        auto node = priority_queue.top();
        priority_queue.pop();
        return node;
    }    
};
*/

#endif
