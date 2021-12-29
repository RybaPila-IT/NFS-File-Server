cmake_minimum_required(VERSION 3.10.2)
project(server)

set(CMAKE_CXX_STANDARD 14)

find_package(Threads)
find_library(socket_lib libsocket.so)
message(STATUS ${socket_lib})

add_executable(server main.cpp)
target_link_libraries(server PRIVATE ${socket_lib} ${CMAKE_THREAD_LIBS_INIT})
