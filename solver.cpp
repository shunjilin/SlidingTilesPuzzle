#include "open.hpp"
#include "array_open.hpp"
#include "closed.hpp"
#include "open_address_closed.hpp"
#include "manhattan_distance_heuristic.hpp"
#include "tile_node.hpp"
#include "astar.hpp"
#include "cxxopts.hpp"
#include "steady_clock_timer.hpp"
#include <array>
#include <string>
#include <iostream>
#include <sstream>

int main(int argc, char *argv[]) {
    int const WIDTH = 4;
    int const HEIGHT = 4;
    int const N_TILES = WIDTH*HEIGHT;
    
    cxxopts::Options options("Sliding Tiles Puzzle Search",
                             "Search algorithms for solving the sliding tiles puzzle.");
    // command line options
    options.add_options()
        ("d,domain", "domain",
         cxxopts::value<std::string>()->default_value("tiles"))
        ("i,initial_state", "initial state configuration",
         cxxopts::value<std::string>());
    
    // parse command line
    auto result = options.parse(argc, argv);

    auto initial_tiles_string = result["initial_state"].as<std::string>();
    std::istringstream iss(initial_tiles_string);
    
    std::array<uint8_t, N_TILES> initial_tiles;

    // read tiles
    for (int i = 0; i < N_TILES; ++i) {
        std::string tile_string;
        iss >> tile_string;
        initial_tiles[i] = std::stoi(tile_string);
    }
    auto timer = SteadyClockTimer();
    timer.start();
    
    auto initial_node = Tiles::TileNode<WIDTH, HEIGHT>(initial_tiles);
    using Node = decltype(initial_node);
    using Heuristic = decltype(Tiles::ManhattanDistanceHeuristic<WIDTH, HEIGHT>());
    auto astar = AStar<Node, Heuristic, ArrayOpen<Node>,
                       OpenAddressClosed<Node, 205170943> > ();//86028121> >();
    

    std::cout << "Initialization took " << timer.getElapsedTime<milliseconds>()
              << " ms" << std::endl;
    auto path = astar.search(initial_node);
    std::cout << "Took " << timer.getElapsedTime<milliseconds>()
              << " ms to solve (including initialization)" << std::endl;
    std::cout << "Sequence:" << std::endl;
    std::cout << "n moves: " << path.size() - 1 << std::endl;
    for (auto node : path) {
        std::cout << node << std::endl;
    }
    
}
