#include "concurrent_astar.hpp"
#include "concurrent_search.hpp"
#include "cxxopts.hpp"
#include "manhattan_distance_heuristic.hpp"
#include "steady_clock_timer.hpp"
#include "tabulation.hpp"
#include "tile_node.hpp"
#include "util.hpp"
#include <array>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace Tiles;

int const WIDTH = 4;
int const HEIGHT = 4;
int const N_TILES = WIDTH * HEIGHT;

using Node = TileNode<WIDTH, HEIGHT>;
using Heuristic = ManhattanDistanceHeuristic<WIDTH, HEIGHT>;
using HashFunction = TabulationHash<Node, WIDTH * HEIGHT>;
size_t const ClosedEntries = 512927357;
// using HashFunction = std::hash<Node>;

int main(int argc, char *argv[]) {

  cxxopts::Options options(
      "15 Puzzle Solver",
      "Concurrent search algorithms for solving the sliding tiles puzzle.");
  // command line options
  options.add_options()("d,domain", "domain",
                        cxxopts::value<std::string>()->default_value("tiles"))(
      "i,initial_state",
      "initial state configuration"
      "e.g. \"0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15\"",
      cxxopts::value<std::string>()->default_value(""))(
      "g,goal_state",
      "goal state configuration "
      "e.g. \"1 2 3 7 4 5 6 0 8 9 10 11 12 13 14 15\"",
      cxxopts::value<std::string>()->default_value(""))(
      "s,search_algorithm", "search algorithm [concurrent_astar]",
      cxxopts::value<std::string>()->default_value("concurrent_astar"))(
      "h,help", "print help");

  // parse command line
  auto result = options.parse(argc, argv);

  if (result.count("h")) {
    std::cout << options.help({"", "Search"}) << std::endl;
    return EXIT_SUCCESS;
  }

  auto initial_tiles_string = result["initial_state"].as<std::string>();
  auto goal_tiles_string = result["goal_state"].as<std::string>();

  try {
    // read tiles
    // for generic node perhaps modify constructor to take in string
    auto initial_node = Node(getBoardFromString<N_TILES>(initial_tiles_string));
    if (!goal_tiles_string.empty()) {
      Node::setGoalBoard(getBoardFromString<N_TILES>(goal_tiles_string));
    }

    // search algorithm
    auto search_string = result["search_algorithm"].as<std::string>();
    std::unique_ptr<ConcurrentSearch<Node>> concurrent_search_algo;

    auto timer = SteadyClockTimer();
    timer.start();

    if (search_string == "concurrent_astar") {
      concurrent_search_algo = std::make_unique<
          ConcurrentAStar<Node, Heuristic, HashFunction, ClosedEntries>>();
    } else {
      std::cerr << "Invalid search algorithm option: "
                << "\"" << search_string << "\"\n";
      return EXIT_FAILURE;
    }

    std::cout << timer.getElapsedTime<milliseconds>() << " ms to initialize\n";

    auto path = concurrent_search_algo->search(initial_node);

    std::cout << timer.getElapsedTime<milliseconds>()
              << " ms to solve (including initialization)\n"
              << *concurrent_search_algo << "\n"
              << "n moves: " << path.size() - 1 << "\n"
              << "sequence:\n";

    for (auto node : path) {
      std::cout << node << "\n";
    }
  }
  // handle errors
  catch (const std::invalid_argument &ia) {
    std::cerr << "Invalid argument for initial state: " << ia.what() << " : "
              << "\"" << initial_tiles_string << "\"\n";
    return EXIT_FAILURE;
  } catch (const std::bad_alloc &ba) {
    std::cerr << "Memory allocation failed : " << ba.what() << "\n";
  } catch (const std::exception &e) {
    std::cerr << "Search failed: " << e.what() << "\n";
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
