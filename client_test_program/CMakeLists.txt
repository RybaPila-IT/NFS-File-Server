cmake_minimum_required(VERSION 3.10.2)
project(client_test_program)

set(CMAKE_CXX_STANDARD 14)

find_library(file_system_manager_lib libfile_system_manager.so)
find_library(socket_lib libsocket.so)
find_library(message_lib libmessage.so)

message(STATUS ${socket_lib})
message(STATUS ${message_lib})
message(STATUS ${file_system_manager_lib})

add_executable(client_test_program
        main.cpp
        test_lseek.cpp test_lseek.h
        test_open_close.cpp test_open_close.h)

target_link_libraries(client_test_program PRIVATE
        ${file_system_manager_lib}
        ${socket_lib}
        ${message_lib})
