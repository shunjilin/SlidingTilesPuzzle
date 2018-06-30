#ifndef ACTION_HPP
#define ACTION_HPP

#include <memory>

struct IAction {
};

class Action {
    std::unique_ptr<IAction> pimpl;
public:
    Action(IAction const &action);
    Action(Action const & other);
};

#endif
