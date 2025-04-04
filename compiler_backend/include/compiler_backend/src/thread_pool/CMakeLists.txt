add_library(thread_pool STATIC
    src/thread_pool.cpp
)

target_include_directories(thread_pool PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
