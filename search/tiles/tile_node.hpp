#ifndef TILE_NODE_HPP
#define TILE_NODE_HPP

#include <array>
#include <optional>
#include "tiles.hpp"

namespace Tiles {
    
    template <typename Heuristic>
    struct TileNode {

        Board board;

        // caching to prevent regeneration of parent node
        MOVE prev_move = NONE;
        
        unsigned char cost = 0; // g-value

        // constructor
        TileNode(Board board,
		 MOVE prev_move = NONE,
                 unsigned char cost = 0);

        // get cost of path to node
        int getG() const;

        // get heuristic value of node
        int getH() const;

        // get g + h value
        int getF() const; 

        // get nodes that can be generated from current node
        std::array< std::optional< TileNode<Heuristic> >, N_MOVES >
        getChildNodes() const;

        // get parent node
        std::optional<TileNode<Heuristic> >
        getParent() const;

        // check if node is goal node
        bool isGoal() const;

        bool operator==(TileNode<Heuristic> const & rhs) const {
            return board == rhs.board;
        }
        
        static Heuristic heuristic;
        
        // goal board configuration
        static Board goal_board;
    };

    template <typename Heuristic>
    Heuristic TileNode<Heuristic>::heuristic = Heuristic();

    template <typename Heuristic>
    Board TileNode<Heuristic>::goal_board = Board({0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24});

    template <typename Heuristic>
    TileNode<Heuristic>::TileNode(Board board, MOVE prev_move, unsigned char cost) :
        board(std::move(board)), prev_move(prev_move), cost(cost) {}

    template <typename Heuristic>
    int TileNode<Heuristic>::getG() const {
        return static_cast<int>(cost);
    }

    template <typename Heuristic>
    int TileNode<Heuristic>::getH() const {
        return heuristic.getH(board);
    }

    template <typename Heuristic>
    int TileNode<Heuristic>::getF() const {
        return getG() + getH();
    }

    template <typename Heuristic>
    bool TileNode<Heuristic>::isGoal() const {
        return board == goal_board;
    }

    using uchar = unsigned char;
    
    // generate child nodes from current node
    template <typename Heuristic>
    std::array< std::optional< TileNode<Heuristic> >, N_MOVES >
    TileNode<Heuristic>::getChildNodes() const {
        std::array< std::optional< TileNode<Heuristic> >, N_MOVES > child_nodes;

        if (prev_move != DOWN) {
            auto up_move = moveBlank<UP>(board);
            if (up_move.has_value()) {
                child_nodes[UP] = {std::move(*up_move),  UP,
                                   static_cast<uchar>(cost + 1)};
            }
        }

        if (prev_move != UP) {
            auto down_move = moveBlank<DOWN>(board);
            if (down_move.has_value()) {
                child_nodes[DOWN] = {std::move(*down_move), DOWN,
                                     static_cast<uchar>(cost + 1)};
            }
        }

        if (prev_move != RIGHT) {
            auto left_move = moveBlank<LEFT>(board);
            if (left_move.has_value()) {
                child_nodes[LEFT] = {std::move(*left_move), LEFT,
                                     static_cast<uchar>(cost + 1)};
            }
        }

        if (prev_move != LEFT) {
            auto right_move = moveBlank<RIGHT>(board);
            if (right_move.has_value()) {
                child_nodes[RIGHT] = {std::move(*right_move), RIGHT,
                                      static_cast<uchar>(cost + 1)};
            }
        }
        
        return child_nodes;
    }

    template <typename Heuristic>
    std::optional< TileNode<Heuristic> >
    TileNode<Heuristic>::getParent() const {
        if (prev_move == UP) {
            return TileNode<Heuristic>{*moveBlank<DOWN>(board), NONE};
        }
        if (prev_move == DOWN) {
            return TileNode<Heuristic>{*moveBlank<UP>(board), NONE};
        }
        if (prev_move == LEFT) {
            return TileNode<Heuristic>{*moveBlank<RIGHT>(board), NONE};
        }
        if (prev_move == RIGHT) {
            return TileNode<Heuristic>{*moveBlank<LEFT>(board), NONE};
        }
        return {};
    }
}

// overload default hash
namespace std
{
    template<typename Heuristic>
    struct hash<Tiles::TileNode<Heuristic> >
    {
        size_t
        operator() (const Tiles::TileNode<Heuristic>& node) const
        {
            return hash<Tiles::Board>()(node.board);
        }
    };
}

#endif
