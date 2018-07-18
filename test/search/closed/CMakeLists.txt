# closed test
add_executable(closed_test closed_test.cpp)

target_link_libraries(closed_test
  PRIVATE closed
  PRIVATE gtest
  PRIVATE gmock
  )

target_compile_features(closed_test PUBLIC cxx_std_11)

add_test(closed_test closed_test)
