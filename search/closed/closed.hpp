#ifndef CLOSED_HPP
#define CLOSED_HPP

#include <unordered_set>

// closed list
// requires node to have default hasher for equality comparison
template <typename Node>
struct Closed {

    std::unordered_set<Node> closed;

    // returns true if node needs to be expanded,
    // insert node if not already exist in closed, or if lower f-val than
    // existing closed node
    bool insert(Node node);
};

template <typename Node>
bool Closed<Node>::insert(Node node) {
    auto it = closed.find(node);
    if (it != closed.end()) {
        return false;
    }
    closed.insert(std::move(node));
    return true;
}

#endif
