# search interface

add_library(search INTERFACE)

target_include_directories(search
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
  )

# concurrent search interface

add_library(concurrent_search INTERFACE)

target_include_directories(concurrent_search
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
  )

# astar

add_library(astar INTERFACE)

target_include_directories(astar
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
  )

target_link_libraries(astar
  INTERFACE search
  INTERFACE open_array
  INTERFACE closed_chaining
  )

target_compile_features(astar INTERFACE cxx_std_17)

# idastar

add_library(idastar INTERFACE)

target_include_directories(idastar
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
  )

target_link_libraries(idastar
  INTERFACE search
  )

target_compile_features(idastar INTERFACE cxx_std_17)

# concurrent astar
find_package(Boost)
if (Boost_FOUND)

  add_library(concurrent_astar INTERFACE)

  target_include_directories(concurrent_astar
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
    INTERFACE ${Boost_INCLUDE_DIRS}
    )

  target_link_libraries(concurrent_astar
    INTERFACE concurrent_search
    INTERFACE concurrent_open_array
    INTERFACE concurrent_closed_open_address_pool
    INTERFACE pthread
    INTERFACE boost_system
    )

  target_compile_features(concurrent_astar INTERFACE cxx_std_17)
else()
  message(WARNING "Requires Boost")
endif()
