#include "tile_node.hpp"
#include "manhattan_distance_heuristic.hpp"
#include "search.hpp"
#include "astar.hpp"
#include "astar_pool.hpp"
#include "tabulation.hpp"
#include "cxxopts.hpp"
#include "steady_clock_timer.hpp"
#include <array>
#include <string>
#include <iostream>
#include <sstream>
#include <variant>

using namespace Tiles;

int const WIDTH = 4;
int const HEIGHT = 4;
int const N_TILES = WIDTH*HEIGHT;

using Node = TileNode<WIDTH, HEIGHT>;
using Heuristic = ManhattanDistanceHeuristic<WIDTH, HEIGHT>;
using HashFunction = TabulationHash<Node, WIDTH*HEIGHT>;
//using HashFunction = std::hash<Node>;

int main(int argc, char *argv[]) {

    cxxopts::Options options("Sliding Tiles Puzzle Search",
                             "Search algorithms for solving the sliding tiles puzzle.");
    // command line options
    options.add_options()
        ("d,domain", "domain",
         cxxopts::value<std::string>()->default_value("tiles"))
        ("i,initial_state", "initial state configuration",
         cxxopts::value<std::string>())
        ("s,search_algorithm", "search algorithm",
         cxxopts::value<std::string>());
    
    // parse command line
    auto result = options.parse(argc, argv);
    
    auto timer = SteadyClockTimer();
    timer.start();

    // initial state
    auto initial_tiles_string = result["initial_state"].as<std::string>();
    std::istringstream iss(initial_tiles_string);
    
    std::array<uint8_t, N_TILES> initial_tiles;

    // read tiles
    for (int i = 0; i < N_TILES; ++i) {
        std::string tile_string;
        iss >> tile_string;
        initial_tiles[i] = std::stoi(tile_string);
    }

    // search algorithm
    auto search_string = result["search_algorithm"].as<std::string>();

    std::unique_ptr<Search<Node> > search_algo;

    if (search_string == "astar") {
        search_algo = std::make_unique<AStar<Node, Heuristic, HashFunction> >();
    } else if (search_string == "astar_pool") {
        search_algo = std::make_unique<AStarPool<Node, Heuristic, HashFunction> >();
    } else {
        std::cout << "invalid algorithm option" << "\n";
        throw;
    }

    using Node = Tiles::TileNode<WIDTH, HEIGHT>;
    auto initial_node = Node(initial_tiles);
    
    std::cout <<  timer.getElapsedTime<milliseconds>()
              << " ms to initialize\n";
    auto path = search_algo->search(initial_node);
    
    std::cout << timer.getElapsedTime<milliseconds>()
              << " ms to solve (including initialization)\n";
    std::cout << *search_algo << "\n";
    std::cout << "n moves: " << path.size() - 1 << "\n";
    std::cout << "sequence:\n";
    for (auto node : path) {
        std::cout << node << std::endl;
    }    
}
