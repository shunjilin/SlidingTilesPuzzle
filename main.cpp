#include "open.hpp"
#include "closed.hpp"
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
    int const WIDTH = 5;
    int const HEIGHT = 5;
    int const N_TILES = WIDTH*HEIGHT;
    
    cxxopts::Options options("24 Puzzle Search",
                             "Search algorithms for solving the 24 puzzle.");
    // command line options
    options.add_options()
        ("d,domain", "domain",
         cxxopts::value<std::string>()->default_value("tiles"))
        ("i,initial_state", "initial state configuration",
         cxxopts::value<std::string>());

    std::array<char, N_TILES> initial_tiles;
    
    // parse command line
    auto result = options.parse(argc, argv);

    auto initial_tiles_string = result["initial_state"].as<std::string>();
    std::istringstream iss(initial_tiles_string);

    
    for (int i = 0; i < N_TILES; ++i) {
        std::string tile_string;
        iss >> tile_string;
        initial_tiles[i] = std::stoi(tile_string);
    }
    
    auto board = Tiles::Board<WIDTH, HEIGHT>(initial_tiles);
    using Heuristic = Tiles::ManhattanDistanceHeuristic<WIDTH, HEIGHT>;
    using Node = Tiles::TileNode<WIDTH, HEIGHT, Heuristic>;
    auto initial_node = Node(board);
    auto astar = AStar<Node, Open<Node>, Closed<Node> >();

    auto timer = SteadyClockTimer();
    timer.start();
    auto path = astar.search(initial_node);
    std::cout << "Took " << timer.getElapsedTime<milliseconds>()
              << " ms to solve" << std::endl;
    std::cout << "Sequence:" << std::endl;
    for (auto node : path) {
        std::cout << node.board << std::endl;
    }
    
}
