#ifndef SEARCH_HPP
#define SEARCH_HPP

#include "tiles.hpp"
#include "heuristics.hpp"
#include <memory>

struct Search {

    virtual std::vector<Tiles::Board>
    search(Tiles::Board const& initial_board,
           std::unique_ptr<Tiles::Heuristic> heuristic) = 0;
    
};

#endif
