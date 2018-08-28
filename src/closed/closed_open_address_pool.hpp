#ifndef CLOSED_OPEN_ADDRESS_POOL_HPP
#define CLOSED_OPEN_ADDRESS_POOL_HPP

#include <vector>
#include <optional>
#include <memory>
#include <ostream>
#include <algorithm>
#include "boost/pool/object_pool.hpp"

/* Closed list using open addressing hash table with linear probing
 * stores pointers instead of nodes, requires clients to allocate memory,
 * e.g. using a memory pool
 */

template <typename Node, typename HashFunction, size_t N_Entries>
struct ClosedOpenAddressPool {

    boost::object_pool<Node> pool{1024};//4096 / sizeof(Node)};
    
    static const HashFunction hasher;

    std::vector<Node *> closed;

    ClosedOpenAddressPool() : closed(N_Entries, nullptr) {}

    // returns true if node needs to be expanded,
    // insert node if not already exist in closed, or if lower f-val than
    // existing closed node (reopening)
    bool insert(Node node);

    // given node, return path in closed list by tracing parent nodes
    // assumes node is in the closed list; otherwise returns empty path
    std::vector<Node> getPath(Node const node) const;

    size_t size = 0; // number of nodes in closed list
};

template<typename Node, typename HashFunction, size_t N_Entries>
const HashFunction
ClosedOpenAddressPool<Node, HashFunction, N_Entries>::hasher = HashFunction();

template <typename Node, typename HashFunction, size_t N_Entries>
bool ClosedOpenAddressPool<Node, HashFunction, N_Entries>::insert(Node node) {
    auto idx = hasher(node) % N_Entries;
    while (true) {
        if (closed[idx] == nullptr) { // not found
            auto node_ptr = pool.construct(std::move(node));
            closed[idx] = node_ptr; // insert
            ++size;
            return true;
        } else if (*closed[idx] == node) { // found
            if (getF(node) < getF(*closed[idx])) { // reopening
                auto node_ptr = pool.construct(std::move(node));
                closed[idx] = node_ptr;
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
ClosedOpenAddressPool<Node, HashFunction, N_Entries>::getPath(Node const node) const {
    std::vector<Node> path;
    std::optional<Node> to_find = node;
    auto idx = hasher(*to_find) % N_Entries;

    while (to_find.has_value()) {
        if (*closed[idx] == to_find) { // found
            path.push_back(*closed[idx]);
            to_find = getParent(*closed[idx]);
            if (to_find.has_value()) idx = hasher(to_find.value()) % N_Entries;
        } else {
            ++idx;
            if (idx == N_Entries) idx = 0; // wrap around
            if (closed[idx] == nullptr) throw;
        }
    }

    std::reverse(path.begin(), path.end());
    return path;
}

template <typename Node, typename HashFunction, size_t N_Entries>
std::ostream &operator<<
(std::ostream& os, ClosedOpenAddressPool<Node, HashFunction, N_Entries> const & closed) {
    os <<  "closed list load factor: "
       << (double)(closed.size) / N_Entries << "\n";
    return os;
}

#endif
