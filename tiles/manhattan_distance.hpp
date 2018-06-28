#ifndef MANHATTAN_DISTANCE_HPP
#define MANHATTAN_DISTANCE_HPP

// calculate row index from index in grid of given width
int getRowIdx(int index, int height);

// calculate row index from index in grid of given height
int getColIdx(int index, int width);

// calculate Manhattan distance between two indexes in a grid of dimensions
// width and height
int manhattanDistance(char index1, char index2, int width, int height);

#endif
