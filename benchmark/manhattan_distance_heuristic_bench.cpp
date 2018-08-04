#include <array>
#include <algorithm>
#include <random>
#include <benchmark/benchmark.h>
#include "tile_node.hpp"
#include "manhattan_distance_heuristic.hpp"

// Difference between manhattan distance heuristic and incremental manhattan
// distance heuristic

using Heuristic = Tiles::ManhattanDistanceHeuristic<4, 4>;
using Node = Tiles::TileNode<4, 4>;

static void BM_ManhattanDistanceHeuristic(benchmark::State& state) {
    std::random_device rd;
    std::mt19937 g(rd());
    Heuristic heuristic;
    auto node = Node({0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15});
    for (auto _ : state) {
        for (int i = 0, i_end = state.range(0); i < i_end; ++i) {
            auto next_node = node;
            std::shuffle(next_node.board.begin(), next_node.board.end(), g);
            evalH(next_node, heuristic);
            node = next_node;
        }
    }
}

BENCHMARK(BM_ManhattanDistanceHeuristic)->Range(8, 8<<10);

static void BM_IncrementalManhattanDistanceHeuristic(benchmark::State& state) {
    std::random_device rd;
    std::mt19937 g(rd());
    Heuristic heuristic;
    auto node = Node({0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15});
    for (auto _ : state) {
        for (int i = 0, i_end = state.range(); i < i_end; ++i) {
            auto next_node = node;
            std::shuffle(next_node.board.begin(), next_node.board.end(), g);
            evalH(next_node, node, heuristic);
            node = next_node;
            
        }
    }
}

BENCHMARK(BM_IncrementalManhattanDistanceHeuristic)->Range(8, 8<<10);

BENCHMARK_MAIN();
