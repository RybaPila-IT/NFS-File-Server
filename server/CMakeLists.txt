cmake_minimum_required(VERSION 3.10.2)
project(server)

set(CMAKE_CXX_STANDARD 14)

find_package(Threads)
find_library(socket_lib libsocket.so)
find_library(message_lib libmessage.so)
message(STATUS ${socket_lib} ${message_lib})

add_executable(server main.cpp
        request_handler.cpp request_handler.h
        endpoints/open_file_handler.cpp endpoints/open_file_handler.h
        endpoints/close_file_handler.cpp endpoints/close_file_handler.h
        endpoints/write_file_handler.cpp endpoints/write_file_handler.h
        endpoints/read_file_handler.cpp endpoints/read_file_handler.h
        access_manager.cpp access_manager.h
        )
target_link_libraries(server PRIVATE ${socket_lib} ${message_lib} ${CMAKE_THREAD_LIBS_INIT})
