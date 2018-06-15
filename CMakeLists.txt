cmake_minimum_required(VERSION 3.11)

project("24 Puzzle")

enable_testing()

add_subdirectory(test)

# executables
add_executable(24Puzzle main.cpp)

# warning flags
if (MSVC)
  target_compile_options(24Puzzle PRIVATE /W4)
else()
  target_compile_options(24Puzzle PRIVATE -Wall -Wextra -Wpedantic)
endif()

