cmake_minimum_required(VERSION 3.10.2)
project(client)

set(CMAKE_CXX_STANDARD 14)

find_library(socket_lib libsocket.so)
message(STATUS ${socket_lib})

add_executable(client main.cpp)
target_link_libraries(client PRIVATE ${socket_lib})
