cmake_minimum_required(VERSION 3.20)
project(tempalte_meta_programming LANGUAGES CXX)

# Default C++ standard when Interview is configured standalone
# (harmless when built from the root project, which sets the same).
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Needed for gtest_discover_tests when Interview is configured standalone
# (harmless when built from the root project, which also calls it).
enable_testing()

# Required on glibc < 2.34 sysroots (e.g. the conda toolchain's), where
# pthread is a separate library rather than merged into libc.
find_package(Threads REQUIRED)

# Template meta programming test executable
set(TEMPLATE_META_PROGRAMMING_HEADERS tuple_elems_func_args_match.hpp)
add_executable(template_meta_programming_test
        test/test.cpp
        ${TEMPLATE_META_PROGRAMMING_HEADERS}
)
target_include_directories(template_meta_programming_test PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(template_meta_programming_test PRIVATE Threads::Threads)
