#ifndef CONCURRENT_SEARCH_HPP
#define CONCURRENT_SEARCH_HPP

#include <ostream>
#include <vector>
#include <atomic>

// interface for search algorithms, tracks node generation and expansion counts
template<typename Node>
struct ConcurrentSearch {
    std::atomic<size_t> expanded = 0;
    std::atomic<size_t> generated = 0;
    virtual std::vector<Node> search(Node initial_node) = 0;
    virtual ~ConcurrentSearch() = default;

    // for logging
    virtual std::ostream& print(std::ostream& os) const = 0;
};

template<typename Node>
std::ostream &operator<<(std::ostream & os, ConcurrentSearch<Node> const &search) {
    os << "expanded: " << search.expanded << "\n";
    os << "generated: " << search.generated << "\n";
    search.print(os);
    return os;     
}

#endif
