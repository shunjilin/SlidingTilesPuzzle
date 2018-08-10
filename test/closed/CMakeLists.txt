# closed test
add_executable(closed_test closed_test.cpp)

target_link_libraries(closed_test
  PRIVATE closed
  PRIVATE gtest
  PRIVATE gmock
  )

target_compile_features(closed_test PUBLIC cxx_std_17)

add_test(closed_test closed_test)

# closed list using open addressing test
add_executable(closed_open_address_test closed_open_address_test.cpp)

target_link_libraries(closed_open_address_test
  PRIVATE closed_open_address
  PRIVATE gtest
  PRIVATE gmock
  )

target_compile_features(closed_open_address_test PUBLIC cxx_std_17)

add_test(closed_open_address_test closed_open_address_test)

# closed list using open addressing and pointers test
add_executable(closed_open_address_ptr_test closed_open_address_ptr_test.cpp)

target_link_libraries(closed_open_address_ptr_test
  PRIVATE closed_open_address_ptr
  PRIVATE gtest
  PRIVATE gmock
  )

target_compile_features(closed_open_address_ptr_test PUBLIC cxx_std_17)

add_test(closed_open_address_ptr_test closed_open_address_ptr_test)


# closed list using chaining
add_executable(closed_chaining_test closed_chaining_test.cpp)

target_link_libraries(closed_chaining_test
  PRIVATE closed_chaining
  PRIVATE gtest
  PRIVATE gmock
  )

target_compile_features(closed_chaining_test PUBLIC cxx_std_17)

add_test(closed_chaining_test closed_chaining_test)
