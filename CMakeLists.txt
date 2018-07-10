cmake_minimum_required(VERSION 3.10)

project("24 Puzzle")

# ctest
enable_testing()

add_subdirectory(search)
add_subdirectory(test)

# executables
add_executable(24Puzzle main.cpp)

target_compile_features(24Puzzle PUBLIC cxx_std_14)

target_link_libraries(24Puzzle
  )

# warning flags
if (MSVC)
  target_compile_options(24Puzzle PRIVATE /W4)
else()
  target_compile_options(24Puzzle PRIVATE -Wall -Wextra -Wpedantic)
endif()

## run ctest on build : this does not work if executables have not been compiled
# add_custom_command(TARGET 24Puzzle
#                  POST_BUILD
#                 COMMAND ctest --output-on-failure)
