#include "action.hpp"
#include <memory>

Action::Action(IAction const& action) : pimpl(std::make_unique<IAction>(action)) {}

Action::Action(Action const & other) : pimpl(std::make_unique<IAction>(*other.pimpl)) {}
