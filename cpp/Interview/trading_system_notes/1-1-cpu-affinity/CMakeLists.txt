cmake_minimum_required(VERSION 3.10)
project(1_1_cpu_affinity)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(sched_setaffinity sched_setaffinity.cpp)
add_executable(pthread_setaffinity_np pthread_setaffinity_np.cpp)