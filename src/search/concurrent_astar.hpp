#ifndef CONCURRENT_ASTAR_HPP
#define CONCURRENT_ASTAR_HPP

#include <memory>
#include <vector>
#include <thread>
#include "boost/pool/object_pool.hpp"
#include "concurrent_search.hpp"
#include "concurrent_open_array.hpp"
#include "concurrent_closed_open_address_pool.hpp"

int const N_THREADS = 6;

template <typename Node, typename Heuristic,
          typename HashFunction, size_t ClosedEntries = 512927357,
          typename Closed = ConcurrentClosedOpenAddressPool<Node, HashFunction, ClosedEntries>,
          typename Open = ConcurrentOpenArray<Node, 100, HashFunction, N_THREADS> >
struct ConcurrentAStar : public ConcurrentSearch<Node> {
    
    std::mutex mtx;
    Open open;
    Closed closed;
    Heuristic  heuristic;
    std::atomic<bool> node_found = false;
    std::array<boost::object_pool<Node>, N_THREADS> object_pools;
    std::atomic<int> goal_f = std::numeric_limits<int>::max();
    
    // perform A* search and returns solution path
    std::vector<Node>
    search(Node initial_node) override final {
        evalH(initial_node, heuristic);
        ++ConcurrentSearch<Node>::generated;
        open.push(std::move(initial_node));

        std::vector<std::thread> threads;
        for (int i = 0; i < N_THREADS; ++i) {
            threads.push_back(std::thread(&ConcurrentAStar::worker, this, i));
        }
        for (auto & t : threads) {
            t.join();
        }
        return closed.getPath(Node::goal_node);
    }

    void worker(int thread_id) {
        
        while (true) {
            // synchronize return of all threads, if at least one solution found
            if (node_found == true) {
                if (open.kill_open(thread_id, goal_f)) {
                    return;
                }
            }
            
            auto node = open.pop(thread_id);
            
            if (node.has_value()) {
                if (closed.insert(*node, object_pools[thread_id])) {
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
                            open.push(std::move(*child_node));
                        }
                    }
                }
            }
        }          
    }

    std::ostream& print(std::ostream& os) const override final {
        os << closed;
        return os;
    }
};

#endif
