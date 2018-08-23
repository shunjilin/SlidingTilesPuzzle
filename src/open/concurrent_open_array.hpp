#ifndef OPEN_ARRAY_MUTEX_HPP
#define OPEN_ARRAY_MUTEX_HPP

#include <array>
#include <vector>
#include <mutex>

template <typename Node, int N_THREADS>
struct ConcurrentOpenArray {
    
    static int const MAX_MOVES = 255; // max f and g values

    // bucket indexed by g value
    struct GBucket {
        std::vector<Node> nodes;
    };

    // bucket indexed by f value
    struct FBucket {
        int max_g = -1;
        std::array< GBucket, MAX_MOVES> g_buckets;
    };

    // bucket indexed by thead id
    struct ThreadBucket {
        std::mutex mtx;
        size_t size = 0; // number of entries
        int min_f = MAX_MOVES;
        std::array< FBucket, MAX_MOVES> f_buckets;
    };

    // priority queue, indexed by thread id, f, then g
    std::array<ThreadBucket, N_THREADS> queue;

    // inserts node into open list
    void push(Node node, int thread_id) {
        auto f = getF(node);
        auto g = getG(node);
        
        auto & thread_bucket = queue[thread_id];
        auto & f_bucket = thread_bucket.f_buckets[f];
        auto & g_bucket = f_bucket.g_buckets[g];

        // lock thread bucket
        std::lock_guard<std::mutex> lock(thread_bucket.mtx);

        // update min f, max g if necessary
        if (f < thread_bucket.min_f) thread_bucket.min_f = f;        
        if (g > f_bucket.max_g) f_bucket.max_g = g;
        
        g_bucket.nodes.emplace_back(std::move(node));
        ++thread_bucket.size;
    }

    // pops and returns node from open list
    std::optional<Node> pop(int thread_id) {
        auto & thread_bucket = queue[thread_id];
        
        std::unique_lock<std::mutex> lock(thread_bucket.mtx);
        
        if (thread_bucket.size == 0) return {}; // empty thread bucket
        
        // update min f and max g if necessary
        while (thread_bucket.min_f < MAX_MOVES) {
            auto & f_bucket = thread_bucket.f_buckets[thread_bucket.min_f];
            while (f_bucket.max_g >= 0 &&
                   f_bucket.g_buckets[f_bucket.max_g].nodes.empty()) {
                --f_bucket.max_g;
            }
            if (f_bucket.max_g >= 0) break; // found non empty g bucket
            ++thread_bucket.min_f; // continue searching for valid bucket
        }
        
        auto & f_bucket = thread_bucket.f_buckets[thread_bucket.min_f];
        auto & g_bucket = f_bucket.g_buckets[f_bucket.max_g];
        auto node = g_bucket.nodes.back();
        g_bucket.nodes.pop_back();
        --thread_bucket.size;
        lock.unlock();
        return node;
    }

    int get_min_f(int thread_id) {
        auto & thread_bucket = queue[thread_id];
        std::lock_guard<std::mutex> lock(thread_bucket.mtx);
        return thread_bucket.min_f;
    }
};

#endif
