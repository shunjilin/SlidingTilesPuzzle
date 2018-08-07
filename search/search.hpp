#ifndef SEARCH_HPP
#define SEARCH_HPP

#include <ostream>

// interface for search algorithms
template<typename Node>
struct Search {
    size_t expanded = 0;
    size_t generated = 0;
    virtual std::vector<Node> search(Node initial_node) = 0;
    virtual ~Search() = default;

    // for logging
    virtual std::ostream& print(std::ostream& os) const = 0;
};

template<typename Node>
std::ostream &operator<<(std::ostream & os, Search<Node> const &search) {
    os << "expanded: " << search.expanded << "\n";
    os << "generated: " << search.generated << "\n";
    search.print(os);
    return os;     
}

#endif
