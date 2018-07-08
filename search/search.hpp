#ifndef SEARCH_HPP
#define SEARCH_HPP

#include "node.hpp"
#include <memory>

struct Search {

    virtual std::vector<Node *>
    search(Node const & initial_node) = 0;
    
};

#endif
