cmake_minimum_required(VERSION 3.20)
project(lock_free LANGUAGES CXX)

find_package(Threads REQUIRED)
find_package(GTest REQUIRED)

add_executable(lock_free_test test.cpp)

target_link_libraries(lock_free_test
    PRIVATE
    GTest::gtest
    GTest::gtest_main
    Threads::Threads
)

# Discover tests (requires enable_testing() in the top-level CMakeLists)
include(GoogleTest)
gtest_discover_tests(lock_free_test)
