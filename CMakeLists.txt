cmake_minimum_required(VERSION 3.10)

project("Search")

# ctest
enable_testing()

add_subdirectory(dependencies)
add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(benchmark)
