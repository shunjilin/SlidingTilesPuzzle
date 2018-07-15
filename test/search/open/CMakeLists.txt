# open test
add_executable(open_test open_test.cpp)

target_link_libraries(open_test
  PRIVATE open
  PRIVATE gtest
  PRIVATE gmock
  )

target_compile_features(open_test PUBLIC cxx_std_11)

add_test(open_test open_test)
