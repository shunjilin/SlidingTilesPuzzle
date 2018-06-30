#ifndef NODE_HPP
#define NODE_HPP
#include "action.hpp"

#include <vector>
#include <memory>

struct Node {

    //virtual int getCost() const = 0;

    virtual std::vector<Action> getActions() = 0;
    
    virtual std::unique_ptr<Node> applyAction(Action const & action);

    // assumes action taken was cache
    //virtual void undoLastAction();
};

#endif
