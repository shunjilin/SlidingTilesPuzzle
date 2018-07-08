#ifndef HEURISTICS_HPP
#define HEURISTICS_HPP

#include "node.hpp"

class Heuristic {
public:
    virtual int getHeuristicValue(Node const &) = 0;
};

#endif
