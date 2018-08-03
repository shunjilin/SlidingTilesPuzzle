add_library(closed INTERFACE)

target_include_directories(closed
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
    )

add_library(open_address_closed INTERFACE)

target_include_directories(open_address_closed
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
    )


# open address closed for ptr
add_library(closed_open_address_ptr INTERFACE)

target_include_directories(closed_open_address_ptr
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
    )
