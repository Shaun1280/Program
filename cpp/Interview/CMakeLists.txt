cmake_minimum_required(VERSION 3.20)
project(Interview LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Printer executable
add_executable(printer printer.cpp)

# Smart pointers test executable
set(SMART_POINTER_HEADERS
        smart_pointers/shared_ptr.hpp
        smart_pointers/control_block.hpp
)
add_executable(smart_pointers
        smart_pointers/test.cpp
        ${SMART_POINTER_HEADERS}
)
target_include_directories(smart_pointers PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/smart_pointers
)
