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

    std::array< std::array<size_t, N_Variables>, N_Variables> table;
        
public:
    TabulationHash();
        
    size_t operator()(const Entry & entry) const; // hash value
};

template<class Entry, int N_Variables>
TabulationHash<Entry, N_Variables>::TabulationHash() 
{

    std::mt19937_64 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937_64::result_type>
        dist(0,std::numeric_limits<std::mt19937_64::result_type>::max());
    // fill table with random bitstrings (64 bit)
    for (auto& var : table) {
        for (auto& val : var) {
            val = dist(rng);
        }
    }
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
