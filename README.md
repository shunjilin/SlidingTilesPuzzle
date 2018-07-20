# 24 Puzzle Solver : Search Algorithms

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

To execute solver, run:
```
./24Puzzle -i "[initial state configuration]"
```

where [initial state configuration] is a space separated list of tile numbers, 0-24, with 0 representing the blank tile.

The goal board is defined as:

<pre>
0  1  2  3  4

5  6  7  8  9

10 11 12 13 14

15 16 17 18 19

20 21 22 23 24
</pre>

and represented as "0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24"
