#include "manhattan_distance.hpp"

#include <cstdlib>

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
