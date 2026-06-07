cmake_minimum_required(VERSION 3.20)
project(Interview LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(smart_pointers)
add_subdirectory(trading_system_notes)

# Printer executable
add_executable(printer printer.cpp)



