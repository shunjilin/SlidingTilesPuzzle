cmake_minimum_required(VERSION 3.11)

project("24 Puzzle")

# warning flags
if (MSVC)
  add_compile_options(24Puzzle /W4)
else()
  add_compile_options(24Puzzle -Wall -Wextra -Wpedantic)
endif()

enable_testing()

add_subdirectory(test)

# executables
add_executable(24Puzzle main.cpp)
