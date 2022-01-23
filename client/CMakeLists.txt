cmake_minimum_required(VERSION 3.10.2)
project(client)

set(CMAKE_CXX_STANDARD 14)

find_library(socket_lib libsocket.so)
find_library(message_lib libmessage.so)
message(STATUS ${socket_lib})
message(STATUS ${message_lib})

add_library(file_system_manager SHARED
        NFS_client.cpp
        file_system_manager.cpp file_system_manager.h
        storage.cpp)

target_link_libraries(file_system_manager PRIVATE ${socket_lib} ${message_lib})
install(TARGETS file_system_manager DESTINATION /usr/lib)
install(FILES
        file_system_manager.h
        storage.h
        file.h
        NFS_client.h
        DESTINATION include)
