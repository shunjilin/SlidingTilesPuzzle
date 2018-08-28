#ifndef OPEN_ARRAY_MUTEX_HPP
#define OPEN_ARRAY_MUTEX_HPP

#include <array>
#include <vector>
#include <mutex>
#include "spinlock.hpp"

template <typename Node, int MAX_MOVES, typename HashFunction, int N_THREADS>
struct ConcurrentOpenArray {

    HashFunction hasher;

    // bucket indexed by g value
    struct GBucket {
        std::vector<Node> nodes;
    };

    // bucket indexed by f value
    struct FBucket {
        std::atomic<int> max_g = -1;
        std::array< GBucket, MAX_MOVES> g_buckets;
    };
 

    // bucket indexed by thead id
    struct ThreadBucket {
        spinlock_mutex mtx;
        bool disabled = false;
        size_t size = 0; // number of entries
        int min_f = MAX_MOVES;
        std::array< FBucket, MAX_MOVES> f_buckets;
    };

    // priority queue, indexed by thread id, f, then g
    std::array<ThreadBucket, N_THREADS> queue;

    // inserts node into open list
    void push(Node node) {
        auto f = getF(node);
        auto g = getG(node);

        int thread_id = hasher(node) % N_THREADS;
        
        queue[thread_id].mtx.lock();
        while (queue[thread_id].disabled) {
            queue[thread_id].mtx.unlock();
            ++thread_id;
            if (thread_id == N_THREADS) thread_id = 0;
            queue[thread_id].mtx.lock();
        }
        
        auto & thread_bucket = queue[thread_id];
        auto & f_bucket = thread_bucket.f_buckets[f];
        auto & g_bucket = f_bucket.g_buckets[g];
        
        // update min f, max g if necessary
        if (f < thread_bucket.min_f) thread_bucket.min_f = f;        
        if (g > f_bucket.max_g) f_bucket.max_g = g;
        
        g_bucket.nodes.emplace_back(std::move(node));
        ++thread_bucket.size;
        thread_bucket.mtx.unlock();
    }

    // pops and returns node from open list
    std::optional<Node> pop(int thread_id) {
        
        queue[thread_id].mtx.lock();
        while (queue[thread_id].disabled) {
            queue[thread_id].mtx.unlock();
            
            ++thread_id;
            if (thread_id == N_THREADS) thread_id = 0;
            queue[thread_id].mtx.lock();
        }
        
        auto & thread_bucket = queue[thread_id];
        
        if (thread_bucket.size == 0) {
            thread_bucket.mtx.unlock();
            return {}; // empty thread bucket
        }
        
        // update min f and max g if necessary
        while (thread_bucket.min_f < MAX_MOVES) {
            auto & f_bucket = thread_bucket.f_buckets[thread_bucket.min_f];
            while (f_bucket.max_g >= 0 &&
                   f_bucket.g_buckets[f_bucket.max_g].nodes.empty()) {
                --f_bucket.max_g;
            }
            if (f_bucket.max_g >= 0) break; // found non empty g bucket
            ++thread_bucket.min_f; // continue searching for valid bucket
            //thread_bucket.mtx.unlock();
        }
        
        auto & f_bucket = thread_bucket.f_buckets[thread_bucket.min_f];
        auto & g_bucket = f_bucket.g_buckets[f_bucket.max_g];
        auto node = g_bucket.nodes.back();
        g_bucket.nodes.pop_back();
        
        --thread_bucket.size;
        thread_bucket.mtx.unlock();
        return node;
    }
    
    // lock open list to prevent further pushes into it
    bool kill_open(int thread_id, int goal_f) {
        auto & thread_bucket = queue[thread_id];
        
        thread_bucket.mtx.lock();
        if (thread_bucket.min_f >= goal_f) {
            thread_bucket.disabled = true;
            thread_bucket.mtx.unlock();
            return true;
        }
        thread_bucket.mtx.unlock();
        return false;
    }

    
// for checking correctness
/*
   ~ConcurrentOpenArray() {
   for (auto & thread : queue) {
   int min_f = 0;
   for (int f = 0; f < MAX_MOVES; ++f) {
   for (int g = 0; g < MAX_MOVES; ++g) {
   if (!thread.f_buckets[f].g_buckets[g].nodes.empty()) {
   min_f = f;
   std::cout << min_f << std::endl;
   goto endloop;
   }
   }
   }
   endloop:
   ;
   }
   }
*/

};

#endif
