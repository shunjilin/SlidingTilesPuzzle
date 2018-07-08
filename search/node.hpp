#ifndef NODE_HPP
#define NODE_HPP

#include <vector>
#include <memory>

struct Node {

    virtual std::vector<std::unique_ptr<Node> > getChildNodes() const = 0;

    virtual int getCost() const = 0;

    virtual int getHeuristicValue() const = 0;

};

#endif
