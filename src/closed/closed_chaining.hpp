#ifndef CLOSED_CHAINING_HPP
#define CLOSED_CHAINING_HPP

#include <memory>
#include <optional>
#include <vector>
#include <forward_list>
#include <algorithm>
#include <ostream>

/* Closed list using chained hash table
 * Nodes are allocated individually via a link list
 */

template <typename Node, typename HashFunction, size_t N_Entries>
struct ClosedChaining {

    static const HashFunction hasher;

    std::vector<std::forward_list<Node> > closed;
    
    ClosedChaining() : closed(N_Entries) {}

    // returns true if node needs to be expanded,
    // insert node if not already exist in closed, or if lower f-val than
    // existing closed node (reopening)
    bool insert(Node const & node);

    // given node, return path in closed list by tracing parent nodes
    // assumes node is in the closed list; otherwise returns empty path
    std::vector<Node> getPath(Node const & node) const;

    size_t size = 0;

    size_t probe_count = 0; // number of probes to the hash table

};

template<typename Node, typename HashFunction, size_t N_Entries>
const HashFunction
ClosedChaining<Node, HashFunction, N_Entries>::hasher = HashFunction();

template <typename Node, typename HashFunction, size_t N_Entries>
bool ClosedChaining<Node, HashFunction, N_Entries>::insert(Node const & node) {
    size_t idx = hasher(node) % N_Entries;

    auto & bucket = closed[idx];
    
    ++probe_count;
    
    for (auto it = bucket.begin(); it != bucket.end(); ++it) {
        if (*it == node) { // found
            if (getF(node) < getF(*it)) { // reopening
                *it = node;
                return true;
            }
            return false;
        }
        ++probe_count;
    }
    
    // not found
    bucket.push_front(node); // insert at front of linked list
    ++size;
    return true;
}

template <typename Node, typename HashFunction, size_t N_Entries>
std::vector<Node>
ClosedChaining<Node, HashFunction, N_Entries>::getPath(Node const & node) const {
    std::vector<Node> path;
    std::optional<Node> to_find = node;
    size_t idx = hasher(*to_find) % N_Entries;

    while (to_find.has_value()) {
        auto & bucket = closed[idx];

        auto it = std::find(bucket.begin(), bucket.end(), to_find.value());

        if (it != bucket.end()) { // found
            path.push_back(*it);
            to_find = getParent(*it);
            if (to_find.has_value()) idx = hasher(to_find.value()) % N_Entries;
        }
    }

    std::reverse(path.begin(), path.end());
    return path;
}

template <typename Node, typename HashFunction, size_t N_Entries>
std::ostream &operator<<(std::ostream& os,
                         ClosedChaining<Node, HashFunction, N_Entries> const & closed) {
    os <<  "closed list load factor: "
       << (double)(closed.size) / N_Entries << "\n"
       << "closed list probes: " << closed.probe_count << "\n";
    return os;
}


#endif
