cmake_minimum_required(VERSION 3.10.2)
project(server)

set(CMAKE_CXX_STANDARD 14)

find_package(Threads)
find_library(socket_lib libsocket.so)
find_library(message_lib libmessage.so)
message(STATUS ${socket_lib} ${message_lib})

add_executable(server main.cpp
        RequestHandler.cpp RequestHandler.h
        endpoints/OpenFileHandler.cpp endpoints/OpenFileHandler.h
        AccessManager.cpp AccessManager.h
        )
target_link_libraries(server PRIVATE ${socket_lib} ${message_lib} ${CMAKE_THREAD_LIBS_INIT})
