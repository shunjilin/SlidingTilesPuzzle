# closed test
add_executable(closed_test closed_test.cpp)

target_link_libraries(closed_test
  PRIVATE closed
  PRIVATE gtest
  PRIVATE gmock
  )

target_compile_features(closed_test PUBLIC cxx_std_17)

add_test(closed_test closed_test)

# static closed test
add_executable(open_address_closed_test open_address_closed_test.cpp)

target_link_libraries(open_address_closed_test
  PRIVATE closed
  PRIVATE gtest
  PRIVATE gmock
  )

target_compile_features(open_address_closed_test PUBLIC cxx_std_17)

add_test(open_address_closed_test open_address_closed_test)
