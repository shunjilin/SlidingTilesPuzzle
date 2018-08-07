#ifndef SEARCH_HPP
#define SEARCH_HPP

// interface for search algorithms
template<typename Node>
struct Search {
    virtual std::vector<Node> search(Node initial_node) = 0;
    virtual ~Search() = default;
};

#endif
