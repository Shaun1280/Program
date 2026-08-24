cmake_minimum_required(VERSION 3.20)
project(Interview LANGUAGES CXX)

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

add_subdirectory(smart_pointers)
add_subdirectory(trading_system_notes)
add_subdirectory(lock_free)

# Printer executable
add_executable(printer printer.cpp)
target_link_libraries(printer PRIVATE Threads::Threads)
