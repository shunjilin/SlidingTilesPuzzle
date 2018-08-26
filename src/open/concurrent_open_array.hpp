#ifndef OPEN_ARRAY_MUTEX_HPP
#define OPEN_ARRAY_MUTEX_HPP

#include <array>
#include <vector>
#include <mutex>


/* simple spin lock */
class _spinlock_mutex {
    std::atomic_flag flag;
public:
    _spinlock_mutex(): flag(ATOMIC_FLAG_INIT) {}
    void lock() {
        while (flag.test_and_set(std::memory_order_acquire));
    }
    void unlock() {
        flag.clear(std::memory_order_release);
    }
    bool try_lock() {
        return !flag.test_and_set(std::memory_order_acquire);
    }
};

template <typename Node, typename HashFunction, int N_THREADS>
struct ConcurrentOpenArray {   
    static int const MAX_MOVES = 255; // max f and g values

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
        _spinlock_mutex mtx;
        std::atomic<bool> disabled = false;
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
        /* while (true) {
            
            if (!queue[thread_id].mtx.try_lock()) {
                ++thread_id;
                if (thread_id == N_THREADS) thread_id = 0;
                continue;
            }
            if (queue[thread_id].disabled) {
                queue[thread_id].mtx.unlock();
                ++thread_id;
                if (thread_id == N_THREADS) thread_id = 0;
                continue;
            }
            break;
            }*/
        
        // lock thread bucket
        /*while (!queue[thread_id].mtx.try_lock()) {
                            ++thread_id;
                if (thread_id == N_THREADS) thread_id = 0;
                }*/
        
        queue[thread_id].mtx.lock();
        while (queue[thread_id].disabled) {
            queue[thread_id].mtx.unlock();
            ++thread_id;
            if (thread_id == N_THREADS) thread_id = 0;
            queue[thread_id].mtx.lock();
            }
        
        //std::cout << " peres" << thread_id << std::endl;
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

        /* while (true) {
            while (!queue[thread_id].mtx.try_lock()) {
                ++thread_id;
                if (thread_id == N_THREADS) thread_id = 0;
            }
            if (queue[thread_id].disabled) {
                queue[thread_id].mtx.unlock();
                ++thread_id;
                if (thread_id == N_THREADS) thread_id = 0;
            } else {
                //std::cout << "push" << std::endl;
                break;
            }
            }*/
        
        /*queue[thread_id].mtx.lock();
          while (queue[thread_id].disabled) {
          queue[thread_id].mtx.unlock();
            
          ++thread_id;
            if (thread_id == N_THREADS) thread_id = 0;
            queue[thread_id].mtx.lock();
            }*/
         queue[thread_id].mtx.lock();
          while (queue[thread_id].disabled) {
          queue[thread_id].mtx.unlock();
            
          ++thread_id;
            if (thread_id == N_THREADS) thread_id = 0;
            queue[thread_id].mtx.lock();
            }
        //std::cout << "pop " << thread_id << std::endl;
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

    int get_min_f(int thread_id) {
        auto & thread_bucket = queue[thread_id];
        std::lock_guard<std::mutex> lock(thread_bucket.mtx);
        return thread_bucket.min_f;
    }

    bool kill_thread_bucket(int thread_id, int goal_f) {
        //std::cout << thread_id << " " << std::endl;
        auto & thread_bucket = queue[thread_id];
        //std::lock_guard<std::mutex> lock(thread_bucket.mtx);
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
