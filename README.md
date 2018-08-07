# Sliding Tiles Puzzle Solver : Search Algorithms

## Goal
Efficient and modular search algorithms for domains (e.g. sliding tiles puzzle).

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

Default puzzle is the 15 puzzle.

Puzzle dimensions can be configured in ./solver.cpp (astar) or ./solver2.cpp (optimized astar)

To execute solvers, run:

For Astar with 3-level tie-breaking: min f, max g, LIFO; lazy duplicate detection and manhattan distance heuristic:
```
./Solver -s "astar" -i "[initial state configuration]"
```
For optimized Astar (memory pool and open / closed list that hold pointers to the memory pool) with manhattan distance heuristics:
```
./Solver -s "astar_pool" -i "[initial state configuration]"
```

where [initial state configuration] is a space separated list of tile numbers, 0-15, with 0 representing the blank tile.

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