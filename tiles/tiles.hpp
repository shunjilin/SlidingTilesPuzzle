#ifndef TILES_HPP
#define TILES_HPP

#include <vector>
#include <initializer_list>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <string>

namespace Tiles {

    constexpr int WIDTH = 5, HEIGHT = 5, N_TILES = WIDTH * HEIGHT;

    class Node {
        std::vector<char> tiles;
        //char blank_idx = 0;
    public:
        Node(std::initializer_list<char> tiles_list) :
            tiles(tiles_list) {}
        
        friend std::ostream &operator<<(std::ostream& os, const Node& node) {
            for (auto tile : node.tiles) {
                os << std::to_string(tile) << " ";
            }
            return os;
        }
    };

}

#endif
