#include "tiles.hpp"
#include <initializer_list>
#include <cstdio>

int main() {
    auto tiles = std::array<char, Tiles::N_TILES>
        ({{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
           15, 16, 17, 18, 19, 20, 21, 22, 23, 24}});
    auto board1 = Tiles::Board(tiles);
    
    auto board2 = Tiles::Board(tiles);

    std::array<Tiles::Board, 2> boards = {{board1, board2}};
    std::cout << sizeof(boards) << std::endl;
}
