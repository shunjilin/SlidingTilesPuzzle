#ifndef HEURISTICS_HPP
#define HEURISTICS_HPP

#include "tiles.hpp"
#include <array>
#include <cstdlib>

namespace Tiles {

    class Heuristic {
    public:
        virtual int getHeuristicValue(const Board& board) = 0;
    };

    class ManhattanDistanceHeuristic : Heuristic {
    private:
        // 2-D array for calculating each tile's manhattan distance
        std::array< std::array<char, N_TILES>, N_TILES> table;
    public:
        ManhattanDistanceHeuristic();
        
        int getHeuristicValue(const Board& board) override final;
    };

    // calculate row index from index in grid of given width
    int getRowIdx(int index, int width) {
        return index / width;
    }

    // calculate row index from index in grid of given height
    int getColIdx(int index, int height) {
        return index / height;
    }

    // calculate Manhattan distance between two indexes in a grid of dimensions
    // width and height
    int ManhattanDistance(char index1, char index2, int width, int height) {
        return abs(getRowIdx(index1, width) - getRowIdx(index2, width)) +
            abs(getColIdx(index1, height) - getColIdx(index2, height));
    };
}

#endif
