#ifndef UTIL_HPP
#define UTIL_HPP

#include <array>
#include <sstream>

template<int N_TILES>
std::array<uint8_t, N_TILES>
getBoardFromString(std::string const &board_string) {
  std::array<uint8_t, N_TILES> board;
  std::istringstream iss(board_string);
  for (int i = 0; i < N_TILES; ++i) {
    std::string tile_string;
    iss >> tile_string;
    board[i] = std::stoi(tile_string);
  }
  return board;
}

#endif
