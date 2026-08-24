cmake_minimum_required(VERSION 3.20)
project(CPP LANGUAGES CXX)

# Default C++ standard for all targets (individual targets may override).
# Previously this came implicitly from the Conan toolchain (cppstd=26).
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

add_subdirectory(Interview)
add_subdirectory(WeeklyCPP)
