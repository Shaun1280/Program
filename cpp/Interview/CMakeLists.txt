cmake_minimum_required(VERSION 3.20)
project(Interview LANGUAGES CXX)

if(EXISTS ${CMAKE_CURRENT_BINARY_DIR}/conan_toolchain.cmake)
    include(${CMAKE_CURRENT_BINARY_DIR}/conan_toolchain.cmake)
endif()

add_subdirectory(smart_pointers)
add_subdirectory(trading_system_notes)

# Printer executable
add_executable(printer printer.cpp)

