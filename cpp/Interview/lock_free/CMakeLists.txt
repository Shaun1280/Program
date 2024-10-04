cmake_minimum_required(VERSION 3.10)
project(lock_free)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set the root directory (adjust this path as needed)
set(ROOTDIR ${CMAKE_SOURCE_DIR}/..)

# Set the library directory (adjust this path as needed)
set(LIB_DIR ${ROOTDIR}/lib)

# Add include directories
include_directories(${ROOTDIR}/include)

# Find pthread
find_package(Threads REQUIRED)

# Add the executable
add_executable(test test.cpp)

# Link libraries
target_link_libraries(test 
    PRIVATE 
    gtest
    gtest_main
    pthread
)

# Discover tests
include(GoogleTest)
gtest_discover_tests(test)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})