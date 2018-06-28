#ifndef ASTAR_HPP
#define ASTAR_HPP

#include "search.hpp"
#include <memory>
#include <vector>

struct AStar : Search {

    // perform astar search: lazy with reopenings
    std::vector<Tiles::Board>
    search(Tiles::Board const& initial_board,
           std::unique_ptr<Tiles::Heuristic> heuristic) override final;
};

#endif
