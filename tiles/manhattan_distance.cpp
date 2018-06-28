#include "manhattan_distance.hpp"

#include <cstdlib>

// calculate row index from index in grid of given width
int getRowIdx(int index, int height) {
    return index / height;
}

// calculate row index from index in grid of given height
int getColIdx(int index, int width) {
    return index % width;
}

// calculate Manhattan distance between two indexes in a grid of dimensions
// width and height
int manhattanDistance(char index1, char index2, int width, int height) {
    return abs(getRowIdx(index1, height) - getRowIdx(index2, height)) +
        abs(getColIdx(index1, width) - getColIdx(index2, width));
};
