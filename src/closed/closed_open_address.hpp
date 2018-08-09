#ifndef CLOSED_OPEN_ADDRESS_HPP
#define CLOSED_OPEN_ADDRESS_HPP

#include <array>
#include <functional>
#include <optional>
#include <iostream>

// open addressing to minimize memory allocations
// TODO: use bool or optional to indicate if entry is filled? Right now uses
// default constructor as null entry;
template <typename Node, typename HashFunction, size_t N_Entries>
struct ClosedOpenAddress {
    static const Node NullEntry;

    static const HashFunction hasher;
    
    std::vector<Node> closed;

    ClosedOpenAddress() : closed(N_Entries, Node()) {}
                                
    // returns true if node needs to be expanded,
    // insert node if not already exist in closed, or if lower f-val than
    // existing closed node
    bool insert(Node node);

    std::vector<Node> getPath(Node const & node) const;
    
    size_t size = 0;
};

template<typename Node, typename HashFunction, size_t N_Entries>
Node const ClosedOpenAddress<Node, HashFunction, N_Entries>::NullEntry = Node();

template<typename Node, typename HashFunction, size_t N_Entries>
const HashFunction ClosedOpenAddress<Node, HashFunction, N_Entries>::hasher = HashFunction();


template <typename Node, typename HashFunction, size_t N_Entries>
bool ClosedOpenAddress<Node, HashFunction, N_Entries>::insert(Node node) {
    size_t idx = hasher(node) % N_Entries;
    while (true) {
        if (closed[idx] == NullEntry) { // not found
            closed[idx] = node; // insert
            ++size;
            return true;
        } else if (closed[idx] == node) { // found
            if (getF(node) < getF(closed[idx])) { // reopening
                closed[idx] = node;
                return true;
            }
            return false;
        } else { // collision
            ++idx;
            if (idx == N_Entries) idx = 0; //wrap around
        }
    }
}

template <typename Node, typename HashFunction, size_t N_Entries>
std::vector<Node>
ClosedOpenAddress<Node, HashFunction, N_Entries>::getPath(Node const &node) const {
    std::vector<Node> path;
    std::optional<Node> to_find = node;
    size_t idx = hasher(*to_find) % N_Entries;

    while (to_find.has_value()) {
        if (closed[idx] == *to_find) { // found
            path.push_back(closed[idx]);
            to_find = getParent(closed[idx]);
            if (to_find.has_value()) idx = hasher(*to_find) % N_Entries;
        } else {
            ++idx;
            if (idx == N_Entries) idx = 0; // wrap around
            if (closed[idx] == NullEntry) throw;
            to_find = closed[idx];
        }
    }
    std::reverse(path.begin(), path.end());
    return path;
}

template <typename Node, typename HashFunction, size_t N_Entries>
std::ostream &operator<<(std::ostream& os,
                         ClosedOpenAddress<Node, HashFunction, N_Entries> const & closed) {
    os <<  "closed list load factor: "
       << (double)(closed.size) / N_Entries << std::endl;
    return os;
}

#endif
