add_library(distributed_linking STATIC
    src/distributed_linker.cpp
)

target_include_directories(distributed_linking PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
