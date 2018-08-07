#ifndef TABULATION_HASH_HPP
#define TABULATION_HASH_HPP

//#define TWISTED // optimization for twisted tabulation

#include <random>
#include <limits>
#include <iostream>
#include <array>
#include <algorithm>
#include <memory>

// Zobrist hashing a.k.a Simple Tabulation Hashing
// Using Mersenne Twister 64 bit pseudorandom number generator, seeded by
// Minimal Standard generator (simple multiplicative congruential)
template<typename Entry, int N_Variables>
class TabulationHash {
    // for seeding Mersenne Twister array of internal states
    static size_t master_seed;
    static std::minstd_rand master_eng;
    static std::uniform_int_distribution<unsigned> master_dis;

    // actual number generator for zobrist hashing
    static unsigned get_rand_seed();
    static std::unique_ptr<std::mt19937_64> mt_ptr; 
    static std::uniform_int_distribution<size_t> dis;

    size_t get_rand_bitstring() const;

    std::array< std::array<size_t, N_Variables>, N_Variables> table;
        
public:
    TabulationHash();
        
    size_t operator()(const Entry & entry) const; // hash value
};

template<class Entry, int N_Variables>
size_t TabulationHash<Entry, N_Variables>::master_seed = 1; // default seed

template<class Entry, int N_Variables>
std::minstd_rand TabulationHash<Entry, N_Variables>::master_eng(master_seed);

template<class Entry, int N_Variables>
std::uniform_int_distribution<unsigned>
TabulationHash<Entry, N_Variables>::master_dis(0, std::numeric_limits<unsigned>::max());

template<class Entry, int N_Variables>
unsigned TabulationHash<Entry, N_Variables>::get_rand_seed() {
    return master_dis(master_eng);
}

template<class Entry, int N_Variables>
std::uniform_int_distribution<size_t>
TabulationHash<Entry, N_Variables>::dis(0, std::numeric_limits<size_t>::max());

template<class Entry, int N_Variables>
std::unique_ptr<std::mt19937_64> TabulationHash<Entry, N_Variables>::mt_ptr = nullptr;
    
template<class Entry, int N_Variables>
TabulationHash<Entry, N_Variables>::TabulationHash() 
{
    // initialize seeds for mersenne twister
    if (!mt_ptr) {
        
        std::array<unsigned, std::mt19937_64::state_size> seed_data;
        
        std::generate(std::begin(seed_data), std::end(seed_data),
                      get_rand_seed);
        
        std::seed_seq seq(std::begin(seed_data), std::end(seed_data));
        
        mt_ptr = std::make_unique<std::mt19937_64>(std::mt19937_64(seq));
       
    }

    // fill table with random bitstrings (64 bit)
    for (auto& var : table) {
        for (auto& val : var) {
            val = get_rand_bitstring();
        }
    }
}

template<class Entry, int N_Variables>
size_t TabulationHash<Entry, N_Variables>::get_rand_bitstring() const {
    return dis(*mt_ptr);
}

template<class Entry, int N_Variables>
size_t TabulationHash<Entry, N_Variables>::operator()(const Entry& entry) const {
    size_t hash_value = 0;
#ifdef TWISTED
    size_t i = 0;
    for (; i < table.size() - 1; ++i) {
        hash_value ^= table[i][entry[i]];
    }
        
    hash_value ^= table[i][(entry[i] ^ hash_value) % table[i].size()];
#else
    int i = 0;
    for (auto it : entry) {
        hash_value ^= table[i][it];
        ++i;
    }
#endif
    return hash_value;
}

#endif
