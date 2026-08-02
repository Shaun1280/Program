cmake_minimum_required(VERSION 3.10)
project(WeeklyCPP LANGUAGES CXX)

if(EXISTS ${CMAKE_CURRENT_BINARY_DIR}/conan_toolchain.cmake)
    include(${CMAKE_CURRENT_BINARY_DIR}/conan_toolchain.cmake)
endif()
