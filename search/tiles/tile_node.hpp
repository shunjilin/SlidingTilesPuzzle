#ifndef TILE_NODE_HPP
#define TILE_NODE_HPP

#include "tiles.hpp"

namespace Tiles {
    
    template <typename Heuristic>
    struct TileNode {

        Board board;
        // goal board configuration
        static Board goal_board;
        int cost = 0; // g-value

        // caching to prevent regeneration of parent node
        MOVE prev_move = NONE;

        // constructor
        TileNode(Board board,
		 MOVE prev_move = NONE);

        // get cost of path to node
        int getCost() const;

        // get heuristic value of node
        int getHeuristicValue() const;

        // get nodes that can be generated from current node
        std::array< std::optional< TileNode<Heuristic> >, N_MOVES >
        getChildNodes() const;

        static Heuristic heuristic;

    };

    template <typename Heuristic>
    TileNode<Heuristic>::TileNode(Board board, MOVE prev_move) :
        board(std::move(board)) , prev_move(prev_move) {}

    template <typename Heuristic>
    int TileNode<Heuristic>::getCost() const {
        return cost;
    }

    template <typename Heuristic>
    int TileNode<Heuristic>::getHeuristicValue() const {
        return heuristic.getHeuristicValue(board);
    }

    // generate child nodes from current node
    template <typename Heuristic>
    std::array< std::optional< TileNode<Heuristic> >, N_MOVES >
    TileNode<Heuristic>::getChildNodes() const {
        std::array< std::optional< TileNode<Heuristic> >, N_MOVES > child_nodes;

        if (prev_move != DOWN) {
            auto up_move = moveBlank<UP>(board);
            if (up_move.has_value()) {
                child_nodes[UP] = {std::move(*up_move), UP};
            }
        }

        if (prev_move != UP) {
            auto down_move = moveBlank<DOWN>(board);
            if (down_move.has_value()) {
                child_nodes[DOWN] = {std::move(*down_move), DOWN};
            }
        }

        if (prev_move != RIGHT) {
            auto left_move = moveBlank<LEFT>(board);
            if (left_move.has_value()) {
                child_nodes[LEFT] = {std::move(*left_move), LEFT};
            }
        }

        if (prev_move != LEFT) {
            auto right_move = moveBlank<RIGHT>(board);
            if (right_move.has_value()) {
                child_nodes[RIGHT] = {std::move(*right_move), RIGHT};
            }
        }
        
        return child_nodes;
    }
}

#endif