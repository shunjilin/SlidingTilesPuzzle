# open test
add_executable(open_test open_test.cpp)

target_link_libraries(open_test
  PRIVATE open
  PRIVATE gtest
  PRIVATE gmock
  )

target_compile_features(open_test PUBLIC cxx_std_11)

add_test(open_test open_test)

# array open test
add_executable(array_open_test array_open_test.cpp)

target_link_libraries(array_open_test
  PRIVATE array_open
  PRIVATE gtest
  PRIVATE gmock
  )

target_compile_features(array_open_test PUBLIC cxx_std_11)

add_test(array_open_test array_open_test)
