#ifndef CONCURRENT_CLOSED_OPEN_ADDRESS_POOL_HPP
#define CONCURRENT_CLOSED_OPEN_ADDRESS_POOL_HPP

#include <vector>
#include <optional>
#include <memory>
#include <ostream>
#include <algorithm>
#include "boost/pool/object_pool.hpp"
#include "spinlock.hpp"

/* Concurrent closed list using open addressing hash table with linear probing
 * stores pointers instead of nodes, requires clients to allocate memory,
 * e.g. using a memory pool
 */
template<typename Node>
struct ClosedEntry {
    spinlock_mutex mtx;
    Node * node_ptr = nullptr;
};

template <typename Node, typename HashFunction, size_t N_Entries>
struct ConcurrentClosedOpenAddressPool {

    static const HashFunction hasher;

    std::vector<ClosedEntry<Node>> closed;

    ConcurrentClosedOpenAddressPool() : closed(N_Entries) {}

    // returns true if node needs to be expanded,
    // insert node if not already exist in closed, or if lower f-val than
    // existing closed node (reopening)
    bool insert(Node node, boost::object_pool<Node> & object_pool);

    // given node, return path in closed list by tracing parent nodes
    // assumes node is in the closed list; otherwise returns empty path
    std::vector<Node> getPath(Node node);

    std::atomic<size_t> size = 0; // number of nodes in closed list
};

template<typename Node, typename HashFunction, size_t N_Entries>
const HashFunction
ConcurrentClosedOpenAddressPool<Node, HashFunction, N_Entries>::hasher = HashFunction();

template <typename Node, typename HashFunction, size_t N_Entries>
bool ConcurrentClosedOpenAddressPool<Node, HashFunction, N_Entries>::
insert(Node node, boost::object_pool<Node> & pool) {
    auto idx = hasher(node) % N_Entries;
    while (true) {
        closed[idx].mtx.lock();
        if (closed[idx].node_ptr == nullptr) { // not found
            auto node_ptr = pool.construct(node);
            closed[idx].node_ptr = node_ptr; // insert
            closed[idx].mtx.unlock();
            ++size;
            return true;
        } else if (*closed[idx].node_ptr == node) { // found
            if (getF(node) < getF(*closed[idx].node_ptr)) { // reopening
                auto node_ptr = pool.construct(node);
                closed[idx].node_ptr = node_ptr;
                closed[idx].mtx.unlock();
                return true;
            }
            closed[idx].mtx.unlock();
            return false;
        } else { // collision
            closed[idx].mtx.unlock();
            ++idx;
            if (idx == N_Entries) idx = 0; //wrap around
        }
    }
}

template <typename Node, typename HashFunction, size_t N_Entries>
std::vector<Node>
ConcurrentClosedOpenAddressPool<Node, HashFunction, N_Entries>::getPath(Node node) {
    std::vector<Node> path;
    std::optional<Node> to_find = node;
    auto idx = hasher(*to_find) % N_Entries;

    while (to_find.has_value()) {
        closed[idx].mtx.lock();
        if (*closed[idx].node_ptr == to_find) { // found
            path.push_back(*closed[idx].node_ptr);
            to_find = getParent(*closed[idx].node_ptr);
            if (to_find.has_value()) idx = hasher(to_find.value()) % N_Entries;
            closed[idx].mtx.unlock();
        } else {
            closed[idx].mtx.unlock();
            ++idx;
            if (idx == N_Entries) idx = 0; // wrap around
        }
    }
    std::reverse(path.begin(), path.end());
    return path;
}

template <typename Node, typename HashFunction, size_t N_Entries>
std::ostream &operator<<
(std::ostream& os,
 ConcurrentClosedOpenAddressPool<Node, HashFunction, N_Entries> const & closed) {
    os <<  "closed list load factor: "
       << (double)(closed.size) / N_Entries << "\n";
    return os;
}

#endif
