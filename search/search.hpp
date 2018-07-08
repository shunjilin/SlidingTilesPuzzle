#ifndef SEARCH_HPP
#define SEARCH_HPP

#include "node.hpp"
#include "heuristics.hpp"
#include <memory>

struct Search {

    virtual std::vector<Node *>
    search(Node const & initial_node,
           std::unique_ptr<Heuristic> heuristic) = 0;
    
};

#endif
