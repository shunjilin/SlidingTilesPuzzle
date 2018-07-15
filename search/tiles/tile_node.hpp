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
            child_nodes[0] = moveBlank<UP>(board);
        }

        if (prev_move != UP) {
            child_nodes[1] = moveBlank<DOWN>(board);
        }

        if (prev_move != RIGHT) {
            child_nodes[2] = moveBlank<LEFT>(board);
        }

        if (prev_move != LEFT) {
            child_nodes[3] = moveBlank<RIGHT>(board);
        }
        
        return child_nodes;
    }
}

#endif
