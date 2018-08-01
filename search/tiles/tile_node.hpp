#ifndef TILE_NODE_HPP
#define TILE_NODE_HPP

#include <array>
#include <optional>
#include <numeric>
#include <limits>
#include "tiles.hpp"

namespace Tiles {

    using uchar = unsigned char;

    // returns goal board, where value at each index = index
    template<int WIDTH, int HEIGHT>
    Board<WIDTH, HEIGHT> getGoalBoard() {
        std::array<char, WIDTH*HEIGHT> tiles;
        for (int i = 0; i < WIDTH*HEIGHT; ++i) {
            tiles[i] = i;
        }
        return Board<WIDTH, HEIGHT>(tiles);
    }
    
    template <int WIDTH, int HEIGHT>
    struct TileNode {
        
        // goal board configuration
        static Board<WIDTH, HEIGHT> goal_board;

        Board<WIDTH, HEIGHT> board;

        // caching to prevent regeneration of parent node
        MOVE prev_move = NONE;
        
        unsigned char cost = 0; // g-value
         // cached h_val;
        unsigned char h = std::numeric_limits<unsigned char>::max();

        bool isHCached() const {
            return h != std::numeric_limits<unsigned char>::max();
        }
        
        // constructor
        TileNode(Board<WIDTH, HEIGHT> board,
		 MOVE prev_move = NONE,
                 unsigned char cost = 0) :
            board(std::move(board)), prev_move(prev_move), cost(cost) {}

        bool operator==(TileNode<WIDTH, HEIGHT> const & rhs) const {
            return board == rhs.board;
        }

        // get nodes that can be generated from current node
        std::array< std::optional< TileNode<WIDTH, HEIGHT> >, N_MOVES >
        getChildNodes() const {
            std::array<
                std::optional< TileNode<WIDTH, HEIGHT> >, N_MOVES
                > child_nodes;
            if (prev_move != DOWN) {
                auto child_node = board.moveBlank(UP);
                if (child_node.has_value()) {
                    child_nodes[UP] = {std::move(*child_node),  UP,
                                       static_cast<uchar>(cost + 1)};
                }
            }
            if (prev_move != LEFT) {
                auto child_board = board.moveBlank(RIGHT);
                if (child_board.has_value()) {
                    child_nodes[RIGHT] = {std::move(*child_board), RIGHT,
                                          static_cast<uchar>(cost + 1)};
                }
            }
            if (prev_move != RIGHT) {
                auto child_board = board.moveBlank(LEFT);
                if (child_board.has_value()) {
                    child_nodes[LEFT] = {std::move(*child_board), LEFT,
                                         static_cast<uchar>(cost + 1)};
                }
            }
            if (prev_move != UP) {
                auto child_board = board.moveBlank(DOWN);
                if (child_board.has_value()) {
                    child_nodes[DOWN] = {std::move(*child_board), DOWN,
                                         static_cast<uchar>(cost + 1)};
                }
            }
            return child_nodes;   
        }

        // get parent node
        std::optional<TileNode<WIDTH, HEIGHT> >
        getParent() const {     
            if (prev_move == UP) {
                return TileNode<WIDTH, HEIGHT>{*board.moveBlank(DOWN), NONE};
            }
            if (prev_move == DOWN) {
                return TileNode<WIDTH, HEIGHT>{*board.moveBlank(UP), NONE};
            }
            if (prev_move == LEFT) {
                return TileNode<WIDTH, HEIGHT>{*board.moveBlank(RIGHT), NONE};
            }
            if (prev_move == RIGHT) {
                return TileNode<WIDTH, HEIGHT>{*board.moveBlank(LEFT), NONE};
            }
            return {};
        }
    };

    template <int WIDTH, int HEIGHT>
    Board<WIDTH, HEIGHT> TileNode<WIDTH, HEIGHT>::goal_board =
        Tiles::getGoalBoard<WIDTH, HEIGHT>();

    // free functions, loose coupling, take advantage of argument dependent
    // lookup

    // evalutate and cache h value
    template <int WIDTH, int HEIGHT, typename Heuristic>
    void evalH(TileNode<WIDTH, HEIGHT> & node, Heuristic const & heuristic) {
        if (!node.isHCached()) {
            node.h = heuristic.getH(node.board);
        }
    }
    
    // get cost of path to node
    template <int WIDTH, int HEIGHT>
    int getG(TileNode<WIDTH, HEIGHT> const & node) {
        return static_cast<int>(node.cost);
    }

    // get heuristic value of node
    template<int WIDTH, int HEIGHT>
    int getH(TileNode<WIDTH, HEIGHT> const & node) {
        return static_cast<int>(node.h);
    }

    // get g + h value
    template<int WIDTH, int HEIGHT>
    int getF(TileNode<WIDTH, HEIGHT> const & node) {
        return getG(node) + getH(node);
    }

    // check if node is goal node
    template<int WIDTH, int HEIGHT>
    bool isGoal(TileNode<WIDTH, HEIGHT> const & node) {
        return node.board == node.goal_board;
    }
}

// overload default hash
namespace std
{
    template<int WIDTH, int HEIGHT>
    struct hash<Tiles::TileNode<WIDTH, HEIGHT> >
    {
        size_t
        operator() (const Tiles::TileNode<WIDTH, HEIGHT>& node) const
        {
            size_t result = 0;
            for (auto i = 0; i < WIDTH*HEIGHT; ++i) {
                result = result * 31 + hash<int>()(node.board.tiles[i]);
            }
            return result;
        }
    };
}

#endif
