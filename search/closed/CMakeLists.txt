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

# closed list using open addressing and holding pointers
add_library(closed_open_address_ptr INTERFACE)

target_include_directories(closed_open_address_ptr
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
    )
