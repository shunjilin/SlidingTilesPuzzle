add_library(closed INTERFACE)

target_include_directories(closed
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
    )

add_library(open_address_closed INTERFACE)

target_include_directories(open_address_closed
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
    )
