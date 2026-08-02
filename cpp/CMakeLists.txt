cmake_minimum_required(VERSION 3.20)
project(CPP LANGUAGES CXX)

if(EXISTS ${CMAKE_CURRENT_BINARY_DIR}/conan_toolchain.cmake)
    include(${CMAKE_CURRENT_BINARY_DIR}/conan_toolchain.cmake)
endif()

add_subdirectory(Interview)
add_subdirectory(WeeklyCPP)
