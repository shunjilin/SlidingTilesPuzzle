#ifndef TILES_HPP
#define TILES_HPP

#include <array>
#include <initializer_list>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <string>

namespace Tiles {

    constexpr int WIDTH = 5, HEIGHT = 5, N_TILES = WIDTH * HEIGHT;

    class Node {
        std::array<char, N_TILES> tiles;
        char blank_idx = 0;
    public:
        Node(std::initializer_list<char> tiles_list)  {
            std::copy(tiles_list.begin(), tiles_list.end(), tiles.begin());
            // temporary for testing
            std::cout << *this;
            std::cout << blank_idx;
        }
        
        friend std::ostream &operator<<(std::ostream& os, const Node& node) {
            for (auto tile : node.tiles) {
                os << std::to_string(tile) << " ";
            }
            os << "\n";
            return os;
        }
    };

}

#endif
