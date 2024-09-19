cmake_minimum_required(VERSION 3.5.0)
project(MetaNN VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(MetaNN template.cpp)
add_executable(template template.cpp)

