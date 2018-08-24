#ifndef CONCURRENT_OPEN_ARRAY_FINE_HPP
#define CONCURRENT_OPEN_ARRAY_FINE_HPP

#include <array>
#include <vector>
#include <mutex>

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
struct ConcurrentOpenArrayFine {
    
    static int const MAX_MOVES = 255; // max f and g values

    // bucket indexed by g value
    struct GBucket {
        std::mutex mtx;
        std::vector<Node> nodes;
    };

    // bucket indexed by f value
    struct FBucket {
        std::atomic<int> max_g = 0;
        std::array< GBucket, MAX_MOVES> g_buckets;
    };

    //std::array<std::atomic<int>, MAX_MOVES> max_g_values; // for each f bucket

    // priority queue, indexed by thread id, f, then g
    std::array<FBucket, MAX_MOVES> queue;

    // inserts node into open list
    void push(Node node) {
        auto f = getF(node);
        auto g = getG(node);
        
        auto & f_bucket = queue[f];
        auto & g_bucket = f_bucket.g_buckets[g];

        // lock g bucket
        g_bucket.mtx.lock();
        if (f_bucket.max_g < g) f_bucket.max_g = g;
        //f_bucket.max_g = g;
        //int prev_max_g = f_bucket.max_g;
        
        //while(prev_max_g < g &&
        //  !f_bucket.max_g.compare_exchange_weak(prev_max_g, g))
        //  ;

        // update max g if necessary
        //f_bucket.mtx.lock();
        //if (f_bucket.max_g < g) f_bucket.max_g = g;


        
        g_bucket.nodes.emplace_back(std::move(node));
                g_bucket.mtx.unlock();
                //g_bucket.mtx.unlock();
    }

    // pops and returns node from open list
    std::optional<Node> pop(int min_f) {
        auto & f_bucket = queue[min_f];
        //f_bucket.mtx.lock();
        //if (f_bucket.max_g < 0) f_bucket.max_g = MAX_MOVES-1;
        while (f_bucket.max_g >= 0) {
            
            //auto & g_bucket = f_bucket.g_buckets[g_value];
            auto & g_bucket = f_bucket.g_buckets[f_bucket.max_g];
            g_bucket.mtx.lock();
            
            if (g_bucket.nodes.empty()) {
                --f_bucket.max_g;
                g_bucket.mtx.unlock();
                //--max_g_values[min_f];
            } else {
                auto node = g_bucket.nodes.back();
                g_bucket.nodes.pop_back();
                g_bucket.mtx.unlock();
                return node;             
            }
        }
        //g_bucket.mtx.unlock();
        //if (max_g_values[min_f] == 0) max_g_values[min_f] = MAX_MOVES;
        //std::cout << "empty" << std::endl;
        return {};
    }

};

#endif
