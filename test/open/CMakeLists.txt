# open test
add_executable(open_test open_test.cpp)

target_link_libraries(open_test
  PRIVATE open
  PRIVATE gtest
  PRIVATE gmock
  )

target_compile_features(open_test PRIVATE cxx_std_17)

add_test(open_test open_test)

# array open test
add_executable(open_array_test open_array_test.cpp)

target_link_libraries(open_array_test
  PRIVATE open_array
  PRIVATE gtest
  PRIVATE gmock
  )

target_compile_features(open_array_test PRIVATE cxx_std_17)

add_test(open_array_test open_array_test)
