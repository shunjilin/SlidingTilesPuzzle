#ifndef CLOSED_OPEN_ADDRESS_PTR_HPP
#define CLOSED_OPEN_ADDRESS_PTR_HPP

#include <array>
#include <functional>
#include <optional>
#include <iostream>
#include <memory>

// open addressing to minimize memory allocations
// store pointers to reduce memory footprint / use in conjunction with memory pool
template <typename Node, size_t N_Entries>
struct ClosedOpenAddressPtr {

    static const std::hash<Node> hasher;
    
    std::vector<Node *> closed;

    ClosedOpenAddressPtr() : closed(N_Entries, nullptr) {}
                                
    // returns true if node needs to be expanded,
    // insert node if not already exist in closed, or if lower f-val than
    // existing closed node
    bool insert(Node * node_ptr);

    std::vector<Node> getPath(Node const * node) const;
    
    size_t size = 0;
};

template<typename Node, size_t N_Entries>
const std::hash<Node> ClosedOpenAddressPtr<Node, N_Entries>::hasher = std::hash<Node>();

// insert node pointer into closed list
// return true if node needs to be expanded, false otherwise
// handles reopenings : e.g. inconsistent heuristics
template <typename Node, size_t N_Entries>
bool ClosedOpenAddressPtr<Node, N_Entries>::insert(Node * node_ptr) {
    auto idx = hasher(*node_ptr) % N_Entries;
    while (true) {
        if (closed[idx] != nullptr && *closed[idx] == *node_ptr) { // found
            if (getF(*node_ptr) < getF(*closed[idx])) { // reopening
                closed[idx] = node_ptr;
                return true;
            }
            return false;
        } else if (closed[idx] != nullptr) { // collision
            ++idx;
            if (idx == N_Entries) idx = 0; //wrap around
        } else {
            closed[idx] = node_ptr; // insert
            ++size;
            return true;
        }
    }
}

// given node pointer, trace parent nodes in closed list to return a solution
// path of nodes
template <typename Node, size_t N_Entries>
std::vector<Node>
ClosedOpenAddressPtr<Node, N_Entries>::getPath(Node const * node) const {
    std::cout << "load factor of closed at end of search : " << (double)(size) / N_Entries << std::endl;
    std::vector<Node> path;
    std::optional<Node> to_find = *node;
    auto idx = hasher(*to_find) % N_Entries;

    while (to_find.has_value()) {
        if (*closed[idx] == to_find) { // found
            path.push_back(*closed[idx]);
            to_find = getParent(*closed[idx]);
            idx = hasher(*to_find) % N_Entries;
        } else {
            ++idx;
            if (idx == N_Entries) idx = 0; // wrap around
            if (closed[idx] == nullptr) throw;
            to_find = *closed[idx];
        }
    }
    std::reverse(path.begin(), path.end());
    return path;
}

#endif
