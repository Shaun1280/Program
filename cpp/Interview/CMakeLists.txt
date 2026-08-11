cmake_minimum_required(VERSION 3.20)
project(Interview LANGUAGES CXX)

add_subdirectory(smart_pointers)
add_subdirectory(trading_system_notes)
add_subdirectory(lock_free)

# Printer executable
add_executable(printer printer.cpp)
