add_library(closed INTERFACE)

# simple closed list
target_include_directories(closed
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
    )

# closed list using open addressing
add_library(closed_open_address INTERFACE)

target_include_directories(closed_open_address
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
    )

# closed list using chaining
add_library(closed_chaining INTERFACE)

target_include_directories(closed_chaining
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
  )

# concurrent closed list using chaining
add_library(concurrent_closed_chaining INTERFACE)

target_include_directories(concurrent_closed_chaining
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
  )


# closed list using open addressing and holding pointers, allocation with memory pool
find_package(Boost REQUIRED COMPONENTS system)
if (Boost_FOUND)
  add_library(closed_open_address_pool INTERFACE)

  target_include_directories(closed_open_address_pool
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
    INTERFACE ${Boost_INCLUDE_DIRS}
    INTERFACE boost_system
    )
else()
    message(WARNING "Requires Boost")
endif()


# concurrent closed list using open addressing and holding pointers, allocation with memory pool
add_library(concurrent_closed_open_address_pool INTERFACE)

target_include_directories(concurrent_closed_open_address_pool
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
  )

target_link_libraries(concurrent_closed_open_address_pool
  INTERFACE spinlock
  )
