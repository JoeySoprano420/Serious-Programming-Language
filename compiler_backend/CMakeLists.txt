# This defines the compiler backend as a library
add_library(compiler_backend STATIC
    src/parser.cpp
    src/optimizer.cpp
    src/code_generator.cpp
)

# Include directories for the compiler backend
target_include_directories(compiler_backend PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Link any necessary libraries here
target_link_libraries(compiler_backend PRIVATE
    # Add external libraries for optimization, error handling, etc.
)
