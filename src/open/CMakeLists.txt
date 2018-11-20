# minimal open list
add_library(open INTERFACE)

target_include_directories(open
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
  )

target_compile_features(open INTERFACE cxx_std_14)

# array based open list
add_library(open_array INTERFACE)

target_include_directories(open_array
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
  )
target_compile_features(open_array INTERFACE cxx_std_17)

# array based open list with lock, thread safe
add_library(concurrent_open_array INTERFACE)

target_include_directories(concurrent_open_array
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
  )

target_link_libraries(concurrent_open_array
  INTERFACE spinlock
  )
