#ifndef TILE_NODE_HPP
#define TILE_NODE_HPP

#include "node.hpp"
#include "tiles.hpp"
#include "action.hpp"
#include <vector>

namespace Tiles {

    //enum DIRECTION : char { UP, DOWN, LEFT, RIGHT, COUNT };
    
    struct TileAction : IAction {
        DIRECTION action;
        TileAction(DIRECTION action);
    };

    std::vector<Action> const actions = {
        Action{TileAction{DIRECTION::UP}},
        Action{TileAction{DIRECTION::DOWN}},
        Action{TileAction{DIRECTION::LEFT}},
        Action{TileAction{DIRECTION::RIGHT}}
    };
   

    struct TileNode : Node {
    
        Board board;
        int cost = 0; // g-value

        // caching
        char cur_blank_idx = -1;
        char prev_blank_idx = -1;

        static TileAction action_state;

        TileNode(std::array<char, N_TILES> const &tiles);

        std::vector<Action> getActions() override final;
        
        std::unique_ptr<Node> applyAction(Action const & action) override final;
    };
}
#endif
