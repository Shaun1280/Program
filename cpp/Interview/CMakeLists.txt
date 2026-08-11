cmake_minimum_required(VERSION 3.20)
project(Interview LANGUAGES CXX)

# Needed for gtest_discover_tests when Interview is configured standalone
# (harmless when built from the root project, which also calls it).
enable_testing()

add_subdirectory(smart_pointers)
add_subdirectory(trading_system_notes)
add_subdirectory(lock_free)

# Printer executable
add_executable(printer printer.cpp)
