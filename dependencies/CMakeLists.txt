# build google benchmark (target: benchmark)
# do not build tests of benchmarking lib
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "Suppressing benchmark's tests" FORCE)
add_subdirectory(google/benchmark)

# build tests (targets: gtest_main, gtest, gmock)
add_subdirectory(google/googletest)
