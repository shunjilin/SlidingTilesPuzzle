#ifndef MANHATTAN_DISTANCE_HEURISTIC_HPP
#define MANHATTAN_DISTANCE_HEURISTIC_HPP

#include <cstdlib>
#include <array>
#include "tile_node.hpp"

namespace Tiles {
    
    // calculate row index from index in grid of given width
    int getRowIdx(int index, int width) {
	return index / width;
    }

    // calculate col index from index in grid of given width
    int getColIdx(int index, int width) {
	return index % width;
    }

    // calculate Manhattan distance between two indexes in a grid of given width
    int manhattanDistance(int index1, int index2, int width) {
	return abs(getRowIdx(index1, width) - getRowIdx(index2, width)) +
	    abs(getColIdx(index1, width) - getColIdx(index2, width));
    }

    template<int WIDTH, int HEIGHT>
    struct ManhattanDistanceHeuristic {
        // 2-D array for calculating each tile's manhattan distance
        std::array< std::array<int, WIDTH*HEIGHT>, WIDTH*HEIGHT> table;
        
        ManhattanDistanceHeuristic() {
            // initialize lookup table
            
            // value of 0 for blank tile
            table[0].fill(0);
            
            for (int tile = 1; tile < WIDTH*HEIGHT; ++tile) {
                for (int idx = 0; idx < WIDTH*HEIGHT; ++idx) {
                    table[tile][idx] = manhattanDistance(tile, idx, WIDTH);
                }
            }
        }

        void evalH(TileNode<WIDTH, HEIGHT> & node) const {
            int heuristic_value = 0;
            for (int idx = 0; idx < WIDTH*HEIGHT; ++idx) {
                heuristic_value += table[node.board[idx]][idx];
            }
            node.h_val = heuristic_value;
        }

        void evalHIncremental(TileNode<WIDTH, HEIGHT> & node) const {
            auto parent_blank_idx = getParentBlankIdx(node);
            auto tile_moved = node.board[parent_blank_idx];
            node.h_val += (table[tile_moved][parent_blank_idx] -
                           table[tile_moved][node.blank_idx]);
        }
    };

    // helper function for incremental manhattan heuristic
    template<int WIDTH, int HEIGHT>
    uint8_t getParentBlankIdx(TileNode<WIDTH, HEIGHT> const & node) {
        switch(node.prev_move) {
        case UP:
            return node.blank_idx + WIDTH;
        case DOWN:
            return node.blank_idx - WIDTH;
        case LEFT:
            return node.blank_idx + 1;
        case RIGHT:
            return node.blank_idx - 1;
        default:
            break;
        }
        return node.blank_idx;
    }

    // use non incremental heuristic as optimization seems to give minimal speedup
    template<int WIDTH, int HEIGHT, typename Heuristic>
    void evalH(TileNode<WIDTH, HEIGHT> & node, Heuristic const & heuristic) {
        heuristic.evalH(node);
    }
}

#endif
