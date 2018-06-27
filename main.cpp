#include "tiles.hpp"
#include <initializer_list>
#include <cstdio>

int main() {
    auto board = Tiles::Board{{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
                                15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 0}}};
    std::cout << sizeof(board) << std::endl;
    auto board2 =  Tiles::Board{{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
                                15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 0}}};
    std::array<Tiles::Board, 2> boards = {{board, board2}};
    std::cout << sizeof(boards) << std::endl;
}
