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

        // caching to regenerate parent node
        char prev_blank_idx = -1;

        // constructor
        TileNode(Board board,
		 char prev_blank_idx = std::numeric_limits<char>::max());

        // get cost of path to node
        int getCost() const;

        // get heuristic value of node
        int getHeuristicValue() const;

        // get nodes that can be generated from current node
        std::array<TileNode<Heuristic>, N_MOVES> getChildNodes() const;

        static Heuristic heuristic;

    };

    template <typename Heuristic>
    TileNode<Heuristic>::TileNode(Board board, char prev_blank_idx) :
        board(std::move(board)) , prev_blank_idx(prev_blank_idx) {}

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
    std::array<TileNode<Heuristic>, N_MOVES>
    TileNode<Heuristic>::getChildNodes() const {
        std::array<TileNode<Heuristic>, N_MOVES > child_nodes;
        return child_nodes;
    }

    
}

#endif
