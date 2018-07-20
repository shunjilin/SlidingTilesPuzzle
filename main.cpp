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
    
    cxxopts::Options options("24 Puzzle Search",
                             "Search algorithms for solving the 24 puzzle.");
    // command line options
    options.add_options()
        ("d,domain", "domain",
         cxxopts::value<std::string>()->default_value("tiles"))
        ("i,initial_state", "initial state configuration",
         cxxopts::value<std::string>());

    // parse command line
    auto result = options.parse(argc, argv);

    std::array<char, Tiles::N_TILES> initial_tiles;
    auto initial_tiles_string = result["initial_state"].as<std::string>();
    std::istringstream iss(initial_tiles_string);
    
    for (int i = 0; i < Tiles::N_TILES; ++i) {
        std::string tile_string;
        iss >> tile_string;
        initial_tiles[i] = std::stoi(tile_string);
    }

    auto board = Tiles::Board(initial_tiles);
    using Node = Tiles::TileNode<Tiles::ManhattanDistanceHeuristic>;
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
