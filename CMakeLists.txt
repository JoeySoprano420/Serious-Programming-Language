cmake_minimum_required(VERSION 3.15)
project(AdvancedCompiler)

# Set C++ standard to use
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define source directories for different parts of the project
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(EXTERNAL_LIBS_DIR ${CMAKE_SOURCE_DIR}/external)

# Define executables
add_executable(advanced_compiler ${SOURCE_DIR}/main.cpp)

# Add the compiler backend
add_subdirectory(${SOURCE_DIR}/compiler_backend)
target_link_libraries(advanced_compiler PRIVATE compiler_backend)

# Add thread pool and resource-aware features
add_subdirectory(${SOURCE_DIR}/thread_pool)
target_link_libraries(advanced_compiler PRIVATE thread_pool)

# Add distributed linking mechanism (Cloud and Microservice integration)
add_subdirectory(${SOURCE_DIR}/distributed_linking)
target_link_libraries(advanced_compiler PRIVATE distributed_linking)

# Include the necessary header files
target_include_directories(advanced_compiler PRIVATE
    ${SOURCE_DIR}/compiler_backend/include
    ${SOURCE_DIR}/thread_pool/include
    ${SOURCE_DIR}/distributed_linking/include
)

# Link with external libraries (e.g., for HTTP requests, JSON parsing, etc.)
find_package(CURL REQUIRED)
target_link_libraries(advanced_compiler PRIVATE CURL::CURL)

# Optionally set compilation flags for optimizations
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall")

# Install target (optional, if distributing the executable)
install(TARGETS advanced_compiler DESTINATION /usr/local/bin)
