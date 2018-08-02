set(header_files
    ${CMAKE_CURRENT_SOURCE_DIR}/LoopWaiter.h)

add_library(LoopWaiter INTERFACE)

target_sources(LoopWaiter INTERFACE ${header_files})

target_include_directories(LoopWaiter INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
