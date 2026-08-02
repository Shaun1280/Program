cmake_minimum_required(VERSION 3.20)
project(smart_pointers LANGUAGES CXX)

if(EXISTS ${CMAKE_CURRENT_BINARY_DIR}/conan_toolchain.cmake)
    include(${CMAKE_CURRENT_BINARY_DIR}/conan_toolchain.cmake)
endif()

# Smart pointers test executable
set(SMART_POINTER_HEADERS
        shared_ptr.hpp
        control_block.hpp
        enable_shared_from_this.hpp
        weak_ptr.hpp
        unique_ptr.hpp
        make_helpers.hpp
)
add_executable(smart_pointers_test
        test/test.cpp
        ${SMART_POINTER_HEADERS}
)
target_include_directories(smart_pointers_test PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)
add_executable(shared_ptr_enable_shared_from_test
        test/shared_ptr_enable_shared_from_test.cpp
        ${SMART_POINTER_HEADERS}
)
target_include_directories(shared_ptr_enable_shared_from_test PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR})