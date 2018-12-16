# Sliding Tiles Puzzle Solver : Search Algorithms

15 puzzle solver

## Cloning the repository
```
git clone https://github.com/shunjilin/SlidingTilesPuzzle --recurse-submodules
```

## Dependencies
Boost

## Usage
In root folder, make directory ./build

In ./build, run:
```
cmake -DCMAKE_BUILD_TYPE=Release ..
```
followed by:
```
make
```

To run all tests:
```
ctest --verbose
```

Default puzzle: 15 puzzle

Default heuristic: manhattan distance heuristic

Default hash function: simple tabulation hash (zobrist)

Incremental heuristics or in-place modification is not supported at the moment as they
introduce coupling of domain and search algorithm.

The above parameters can be configured in ./src/solver.cpp and ./src/concurrent_solver.cpp

For help:
```
./src/Solver -h
./src/ConcurrentSolver -h
```

To run solvers:

A Star Search:
```
./src/Solver -s "astar" -i "[initial state configuration]"
```
A Star Search with memory pool
```
./src/Solver -s "astar_pool" -i "[initial state configuration]"
```
Iterative Deepening A Star Search
```
./src/Solver -s "idastar" -i "[initial state configuration]"
```
Concurrent A Star Search (default 6 threads):
```
./src/ConcurrentSolver -s "concurrent_astar" -i "[initial state configuration]"
```

where [initial state configuration] is a space separated list of tile numbers, 0-15, with 0 representing the blank tile.

Note: if bad_alloc is thrown, this may mean that not enough memory is available to initialize the closed list. Change the value ClosedEntries in astar.hpp / astar_pool.hpp to configuret the size of the closed list.

The goal board tiles correspond to the indexes in row-major order, where 0 is the blank tile.
E.g. for the 15 puzzle:

<pre>
0  1  2  3

4  5  6  7

8  9  10 11

12 13 14 15
</pre>

and represented as "0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15"

## Reference
* [Implementing Fast Heuristic Search Code](https://www.aaai.org/ocs/index.php/SOCS/SOCS12/paper/view/5404/5173) by Ethan Andrew Burns, Matthew Hatem, Michael J. Leighton, Wheeler Ruml
