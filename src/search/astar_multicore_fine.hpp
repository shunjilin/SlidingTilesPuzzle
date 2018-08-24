#ifndef ASTAR_MULTICORE_FINE_HPP
#define ASTAR_MULTICORE_FINE_HPP

#include <memory>
#include <vector>
#include <thread>
#include <limits>
#include <mutex>
#include <shared_mutex>
#include <condition_variable>
#include "concurrent_search.hpp"
#include "concurrent_open_array_fine.hpp"
#include "concurrent_closed_chaining.hpp"
#include "tabulation.hpp"

int const N_THREADS_ = 6;

/* Multicore A* Search, using lazy duplicate detection (duplicate detection is
 * only done when nodes are popped from the open list.
 */

template <typename Node, typename Heuristic, typename HashFunction,
          size_t ClosedEntries = 512927357,
          typename Closed = ConcurrentClosedChaining<Node, HashFunction, ClosedEntries> >
struct AStarMulticoreFine : public ConcurrentSearch<Node> {
    
    std::mutex mtx;
    Heuristic heuristic;
    ConcurrentOpenArrayFine<Node, N_THREADS_> open;
    Closed closed;
    HashFunction hasher;
    //std::atomic<int> min_f = std::numeric_limits<int>::max();

    std::atomic<int> goal_f = std::numeric_limits<int>::max();
    std::atomic<bool> node_found = false;
    std::atomic<int> update_counter = 0;

    std::array<std::atomic<int>, 255> update_counters{0};
    std::condition_variable cv;

    // perform A* search and returns solution path
    std::vector<Node>
    search(Node initial_node) override final {

        evalH(initial_node, heuristic);
        //++ConcurrentSearch<Node>::generated;
        int min_f = getF(initial_node);
        open.push(std::move(initial_node));

        std::vector<std::thread> threads;

        //boost::barrier barrier(N_THREADS_);
        for (int i = 0; i < N_THREADS_; ++i) {
            threads.push_back(std::thread(&AStarMulticoreFine::worker, this, min_f)); //std::ref(barrier)));
        }
        for (auto & t : threads) {
            t.join();
        }
        return closed.getPath(Node::goal_node);
    }

        void worker(int min_f) {
        
        while (true) {
            
            // synchronize return of all threads, if at least one solution found
            if (node_found) {
                std::unique_lock<std::mutex> lock(mtx);
                if (min_f >= goal_f) return;
            }

            auto node = open.pop(min_f);

            if (!node.has_value()) {
                ++update_counters[min_f];
                if (update_counters[min_f] == N_THREADS_) {
                    std::unique_lock<std::mutex> lock(mtx);
                    cv.notify_all();
                }
                node = open.pop(min_f);
                if (!node.has_value()) {
                {
                    std::unique_lock<std::mutex> lock(mtx);
                    cv.wait(lock, [&]{ return update_counters[min_f] == N_THREADS_;});
                }
                ++min_f;
                } else {
                    --update_counters[min_f];
                }

                //std::cout << min_f << std::endl;
            }
            if (!node.has_value()) node = open.pop(min_f);
        
            if (node.has_value()) {
                if (closed.insert(*node)) {
                    // check goal node
                    if (isGoal(*node)) {
                        std::unique_lock<std::mutex> lock(mtx);
                        if (getF(*node) < goal_f) goal_f = getF(*node);
                        node_found = true;
                        return;
                    }
                    auto child_nodes = getChildNodes(*node);
                    //++ConcurrentSearch<Node>::expanded;
                    for (auto child_node : child_nodes) {
                        if (child_node.has_value()) {
                            //++ConcurrentSearch<Node>::generated;
                            evalH(*child_node, heuristic);
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
