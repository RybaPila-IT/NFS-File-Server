cmake_minimum_required(VERSION 3.10.2)
project(client)

set(CMAKE_CXX_STANDARD 14)

find_library(SOCKET_LIB libsocket.so)
message(STATUS ${SOCKET_LIB})

add_executable(client main.cpp)
target_link_libraries(client PRIVATE ${SOCKET_LIB})
