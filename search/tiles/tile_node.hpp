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

        TileNode(Board board,
		 char prev_blank_idx = std::numeric_limits<char>::max());

        int getCost() const;

        int getHeuristicValue() const;

        std::vector<TileNode> getChildNodes() const;

        static Heuristic heuristic;

    };

    // constructor for tile node
    template <typename Heuristic>
    TileNode<Heuristic>::TileNode(Board board, char prev_blank_idx) :
        board(std::move(board)) , prev_blank_idx(prev_blank_idx) {}

    template <typename Heuristic>
    int TileNode<Heuristic>::getCost() const {
        return cost;
    }

    template <typename Heuristic>
    int TileNode<Heuristic>::getHeuristicValue() const {
        return heuristic->getHeuristicValue(board);
    }

    // generate child nodes from current node
    template <typename Heuristic>
    std::vector<TileNode<Heuristic> >
    TileNode<Heuristic>::getChildNodes() const {
        std::vector<TileNode<Heuristic> > child_nodes;

        // move blank up
        if (board.blank_idx >= WIDTH) {
            child_nodes.emplace_back
		(TileNode<Heuristic>
		 (getBoardFromBlank(board, board.blank_idx - WIDTH),
		  board.blank_idx)
		 ); 
        }
        // move blank down
        if (board.blank_idx < (WIDTH * (HEIGHT - 1))) {
            child_nodes.emplace_back
		(TileNode<Heuristic>
		 (getBoardFromBlank(board, board.blank_idx + WIDTH),
		  board.blank_idx)
		 );
        }
        // move blank left
        if ((board.blank_idx % WIDTH) != 0) {
            child_nodes.emplace_back
		(TileNode<Heuristic>
		 (getBoardFromBlank(board, board.blank_idx - 1),
                  board.blank_idx)
		 );
        }
        // move blank right
        if ((board.blank_idx % WIDTH) != (WIDTH - 1)) {
            child_nodes.emplace_back
		(TileNode(getBoardFromBlank(board, board.blank_idx + 1),
                 board.blank_idx)
		 );
        }
        return child_nodes;
    };
    
}

#endif
