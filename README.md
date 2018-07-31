# Sliding Tiles Puzzle Solver : Search Algorithms

## Usage
In root folder, make directory ./build

In ./build, run:
```
cmake ..
```
followed by:
```
make
```

To run all tests:
```
ctest --verbose
```

Currently only astar (lazy expansion) with manhattan distance heuristic, and minimal closed and open list implemented.

Puzzle dimensions can be configured in ./solver.cpp
TODO: source generation using CMake to configure domain, puzzle size, search algorithm etc. 

To execute solver, run:
```
./Solver -i "[initial state configuration]"
```

where [initial state configuration] is a space separated list of tile numbers, 0-24, with 0 representing the blank tile.

The goal board tiles correspond to the indexes in row-major order, where 0 is the blank tile.
E.g. for the 15 puzzle:

<pre>
0  1  2  3

4  5  6  7

8  9  10 11

12 13 14 15
</pre>

and represented as "0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15"
