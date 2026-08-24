cmake_minimum_required(VERSION 3.10)
project(1_1_cpu_affinity)

find_package(Threads REQUIRED)

add_executable(sched_setaffinity sched_setaffinity.cpp)
target_link_libraries(sched_setaffinity PRIVATE Threads::Threads)
add_executable(pthread_setaffinity_np pthread_setaffinity_np.cpp)
target_link_libraries(pthread_setaffinity_np PRIVATE Threads::Threads)
