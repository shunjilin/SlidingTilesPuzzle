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
add_executable(open_array_test open_array_test.cpp)

target_link_libraries(open_array_test
  PRIVATE open_array
  PRIVATE gtest
  PRIVATE gmock
  )

target_compile_features(open_array_test PUBLIC cxx_std_11)

add_test(open_array_test open_array_test)

# array with pointers open test
add_executable(open_array_ptr_test open_array_test.cpp)

target_link_libraries(open_array_ptr_test
  PRIVATE open_array_ptr
  PRIVATE gtest
  PRIVATE gmock
  )

target_compile_features(open_array_ptr_test PUBLIC cxx_std_11)
