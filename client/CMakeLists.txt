cmake_minimum_required(VERSION 3.10.2)
project(client)

set(CMAKE_CXX_STANDARD 14)

find_library(socket_lib libsocket.so)
find_library(message_lib libmessage.so)
message(STATUS ${socket_lib} ${message_lib})

add_executable(client main.cpp
        NFS_client.cpp NFS_client.h
        file_system_manager.h file_system_manager.cpp storage.h storage.cpp file.h tests/tests.h tests/tests.cpp)
target_link_libraries(client PRIVATE ${socket_lib} ${message_lib})
