cmake_minimum_required(VERSION 3.5.0)
project(ModernCpp VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ModernCpp test.cpp)
add_executable(tail_type_inferenc  2.3_Type_Inference/tail_type_inferenc.cpp)

