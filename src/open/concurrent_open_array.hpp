#ifndef OPEN_ARRAY_MUTEX_HPP
#define OPEN_ARRAY_MUTEX_HPP

#include <array>
#include <vector>
#include <mutex>
#include <tuple>
#include <shared_mutex>


/* simple spin lock */
class spinlock_mutex_ {
    std::atomic_flag flag;
public:
    spinlock_mutex_(): flag(ATOMIC_FLAG_INIT) {}
    void lock() {
        while (flag.test_and_set(std::memory_order_acquire));
    }
    void unlock() {
        flag.clear(std::memory_order_release);
    }
};


template <typename Node, int N_THREADS>
struct ConcurrentOpenArray {
    
    static int const MAX_MOVES = 255; // max f and g values
    
    struct GBucket {
        //std::mutex mtx;
        std::vector<Node> nodes;
    };

    struct FBucket {
        //std::mutex mtx;
        std::array< GBucket, MAX_MOVES> g_queue;
        int max_g = -1;
    };

    struct ThreadBucket {
        std::mutex mtx;
        std::array< FBucket, MAX_MOVES> f_queue;
        int min_f = MAX_MOVES;
    };

    std::array<ThreadBucket, N_THREADS> queue;

    // inserts node into open list
    void push(Node node, int thread_id) {
        
        //std::cout << "push " << thread_id << std::endl;
        auto f = getF(node);
        auto g = getG(node);
        auto & thread_bucket = queue[thread_id];
        auto & f_bucket = thread_bucket.f_queue[f];
        auto & g_bucket = f_bucket.g_queue[g];

        std::lock_guard<std::mutex> lock(thread_bucket.mtx);

        if (f <= thread_bucket.min_f) { // might contend with pop
            //std::lock_guard<std::mutex> lock(thread_bucket.mtx);
            if (f <= thread_bucket.min_f) {
                thread_bucket.min_f = f;
                if (g > f_bucket.max_g) f_bucket.max_g = g;
                g_bucket.nodes.emplace_back(std::move(node));
                return;
            }
        }
        if (g > f_bucket.max_g) {
            //std::lock_guard<std::mutex> lock(f_bucket.mtx);
            if (g > f_bucket.max_g) {
                f_bucket.max_g = g;
                g_bucket.nodes.emplace_back(std::move(node));
                return;
            }
        }
        //std::lock_guard<std::mutex> lock(g_bucket.mtx);
        g_bucket.nodes.emplace_back(std::move(node));        
    }

    // pops and returns node from open list
    std::optional<Node> pop(int thread_id) {
        //std::cout << "pop " << thread_id << std::endl;
        auto & thread_bucket = queue[thread_id];
        std::unique_lock<std::mutex> lock(thread_bucket.mtx);
        while (thread_bucket.min_f < MAX_MOVES) {
            auto & f_bucket = thread_bucket.f_queue[thread_bucket.min_f];
            while (f_bucket.max_g >= 0 &&
                   f_bucket.g_queue[f_bucket.max_g].nodes.empty()) {
                --f_bucket.max_g;
            }
            if (f_bucket.max_g >= 0) break;
            ++thread_bucket.min_f;
        } 
        if (thread_bucket.min_f == MAX_MOVES) return {};
        
        auto & f_bucket = thread_bucket.f_queue[thread_bucket.min_f];
        auto & g_bucket = f_bucket.g_queue[f_bucket.max_g];
        auto node = g_bucket.nodes.back();
        g_bucket.nodes.pop_back();
        lock.unlock();
        return node;
    }
};

#endif
