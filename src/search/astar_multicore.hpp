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

int const N_THREADS = 3;
int const N_BUCKETS = 1;

/* Multicore A* Search, using lazy duplicate detection (duplicate detection is
 * only done when nodes are popped from the open list.
 */

template <typename Node, typename Heuristic, typename HashFunction,
          size_t ClosedEntries = 512927357,
          typename Closed = ConcurrentClosedChaining<Node, HashFunction, ClosedEntries> >
struct AStarMulticore : public ConcurrentSearch<Node> {
    
    std::mutex mtx;
    Heuristic heuristic;
    ConcurrentOpenArray<Node, HashFunction, N_THREADS*N_BUCKETS> open;
    Closed closed;
    std::atomic<int> goal_f = std::numeric_limits<int>::max();


    std::atomic<bool> node_found = false;

    // perform A* search and returns solution path
    std::vector<Node>
    search(Node initial_node) override final {

        evalH(initial_node, heuristic);
        ++ConcurrentSearch<Node>::generated;
        open.push(std::move(initial_node));

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
        int buckets = 0;
        int returned = 0;
        
        while (true) {
            ++buckets;
            if (buckets == N_BUCKETS) buckets = 0;
            // synchronize return of all threads, if at least one solution found
            if (node_found == true) {
                if (open.kill_thread_bucket(thread_id*N_BUCKETS + buckets, goal_f)) {
                    //std::cout << "returned" << std::endl;
                    ++returned;
                    if (returned == N_BUCKETS) return;
                    //return;
                    
                } else {
                    //std::cout << "failed " << std::endl;
                }
            }
            
            auto node = open.pop(thread_id*N_BUCKETS + buckets);
            //std::cout << " finish pop thread " << thread_id << std::endl;
            if (node.has_value()) {
                if (node_found && getF(*node) >= goal_f) continue;
                if (closed.insert(*node)) {
                    // check goal node
                    if (isGoal(*node)) {
                        node_found = true;
                        std::lock_guard<std::mutex> lock(mtx);
                        if (getF(*node) < goal_f) goal_f = getF(*node);
                        //if (open.kill_thread_bucket(thread_id, goal_f))
                        //return;
                        std::cout << "found" << std::endl;
                        continue;
                    }
                    auto child_nodes = getChildNodes(*node);
                    ++ConcurrentSearch<Node>::expanded;
                    for (auto child_node : child_nodes) {
                        if (child_node.has_value()) {
                            ++ConcurrentSearch<Node>::generated;
                            evalH(*child_node, heuristic);
                            //auto thread_id_to_push = hasher(*child_node) % N_THREADS;
                            open.push(std::move(*child_node));
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
