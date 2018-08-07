cmake_minimum_required(VERSION 3.10)

project("Search")

# ctest
enable_testing()


add_subdirectory(dependencies)
add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(benchmark)

set(CMAKE_BUILD_TYPE Release)
#set(CMAKE_BUILD_TYPE DEBUG)


## run ctest on build : this does not work if executables have not been compiled
# add_custom_command(TARGET 24Puzzle
#                  POST_BUILD
#                 COMMAND ctest --output-on-failure)
