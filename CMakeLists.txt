cmake_minimum_required(VERSION 3.20)
project(C_DZ2 C)

set(CMAKE_C_STANDARD 99)

add_library(core STATIC core.c)
add_library(core_pthread STATIC core core_pthread.c)
add_library(utils STATIC utils.c)

add_executable(main main.c)
target_link_libraries(main core core_pthread utils pthread rt)