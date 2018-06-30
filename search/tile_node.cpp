#include "tile_node.hpp"
#include <memory>

namespace Tiles {

    TileAction::TileAction(DIRECTION action) : action(action) {}

    TileNode::TileNode(std::array<char, N_TILES> const &tiles) :
        board(tiles) , cur_blank_idx(getBlankIdx(board)) {}

    std::vector<Action> getActions() {
        return actions;
    }

    
    

    /*std::vector<std::unique_ptr<Action>> TileNode::getActions() const {
        auto new_blank_idxs = std::vector<std::unique_ptr<Action>>();

        // move blank up
        if (cur_blank_idx >= WIDTH) {
            new_blank_idxs.emplace_back(
                std::make_unique<Action>(TileAction(cur_blank_idx - WIDTH)));
        }

        // move blank down
        if (cur_blank_idx < (WIDTH * (HEIGHT - 1))) {
            new_blank_idxs.emplace_back(
                std::make_unique<Action>(TileAction(cur_blank_idx + WIDTH)));
        }

        // move blank left
        if ((cur_blank_idx % WIDTH) != 0) {
            new_blank_idxs.emplace_back(
                std::make_unique<Action>(TileAction(cur_blank_idx - 1)));
        }

        // move blank right
        if ((cur_blank_idx % WIDTH) != (WIDTH - 1)) {
            new_blank_idxs.emplace_back(
                std::make_unique<Action>(TileAction(cur_blank_idx + 1)));
        }
        return new_blank_idxs;
        };*/

    std::unique_ptr<Node> TileNode::applyAction(Action const & action) {
        return std::make_unique<TileNode>(*this);
    };
};
