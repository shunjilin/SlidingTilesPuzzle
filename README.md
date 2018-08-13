# Sliding Tiles Puzzle Solver : Search Algorithms

## Cloning the repository
```
git clone https://github.com/shunjilin/SlidingTilesPuzzle --recurse-submodules
```

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

The above parameters can be configured in ./solver.cpp

To run solvers:

For AStar with 3-level tie-breaking: min f, max g, LIFO and lazy duplicate detection:
```
./src/Solver -s "astar" -i "[initial state configuration]"
```
For optimized AStar (memory pool and open / closed list that hold pointers to the memory pool):
```
./src/Solver -s "astar_pool" -i "[initial state configuration]"
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
* [Memory pool implementation](https://github.com/cacay/MemoryPool) by Cosku Acay