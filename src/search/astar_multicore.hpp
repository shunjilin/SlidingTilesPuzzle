#ifndef ASTAR_MULTICORE_HPP
#define ASTAR_MULTICORE_HPP

#include <memory>
#include <vector>
#include <thread>
#include <limits>
#include <mutex>
#include "concurrent_search.hpp"
#include "concurrent_open_array.hpp"
#include "concurrent_closed_chaining.hpp"
#include "tabulation.hpp"

int const N_THREADS = 24;

/* Multicore A* Search, using lazy duplicate detection (duplicate detection is
 * only done when nodes are popped from the open list.
 */

template <typename Node, typename Heuristic, typename HashFunction,
          size_t ClosedEntries = 512927357,
          typename Closed = ConcurrentClosedChaining<Node, HashFunction, ClosedEntries> >
struct AStarMulticore : public ConcurrentSearch<Node> {
    
    std::mutex mtx;
    Heuristic heuristic;
    ConcurrentOpenArray<Node, N_THREADS> open;
    Closed closed;
    HashFunction hasher;
    std::atomic<int> goal_f = std::numeric_limits<int>::max();
    std::atomic<int> goal_counter = 0;


    std::atomic<bool> node_found = false;

    // perform A* search and returns solution path
    std::vector<Node>
    search(Node initial_node) override final {

        evalH(initial_node, heuristic);
        ++ConcurrentSearch<Node>::generated;
        open.push(std::move(initial_node), 0);

        std::vector<std::thread> threads;
        for (int i = 0; i < N_THREADS; ++i) {
            threads.push_back(std::thread(&AStarMulticore::worker, this, i));
        }
        for (auto & t : threads) {
            t.join();
        }
        return closed.getPath(Node::goal_node); // TODO: make generic
    }

    void worker(int thread_id) {
        
        while (true) {
            // synchronize return of all threads, if at least one solution found
            if (node_found == true){
                ++goal_counter;
                while (true) {
                    // possibility of finding goal with lower f
                    if (open.get_min_f(thread_id) < goal_f) {
                        --goal_counter;
                        break;
                    }
                    // all threads have reached synchronization point
                    if (goal_counter == N_THREADS) return;
                }
            }
            
            auto node = open.pop(thread_id);
            if (node.has_value()) {
                if (closed.insert(*node)) {
                    // check goal node
                    if (isGoal(*node)) {
                        node_found = true;
                        std::lock_guard<std::mutex> lock(mtx);
                        if (getF(*node) < goal_f) goal_f = getF(*node);
                        continue;
                    }
                    auto child_nodes = getChildNodes(*node);
                    ++ConcurrentSearch<Node>::expanded;
                    for (auto child_node : child_nodes) {
                        if (child_node.has_value()) {
                            ++ConcurrentSearch<Node>::generated;
                            evalH(*child_node, heuristic);
                            auto thread_id_to_push = hasher(*child_node) % N_THREADS;
                            open.push(std::move(*child_node), thread_id_to_push);
                        }
                    }
                }
            }
        }
        
            
    }

    std::ostream&  print(std::ostream& os) const override final {
        os << closed;
        return os;
    }
};

#endif
