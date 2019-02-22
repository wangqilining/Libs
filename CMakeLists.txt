cmake_minimum_required(VERSION 3.13)
project(Libs)

set(CMAKE_CXX_STANDARD 17)
aux_source_directory(./ThreadPool THREAD_SRCS)
add_executable(Libs main.cpp ${THREAD_SRCS} ThreadPool/NJThreadPool.cpp ThreadPool/NJThreadPool.h)
target_link_libraries(Libs pthread)