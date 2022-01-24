cmake_minimum_required(VERSION 3.10.2)
project (message)

set(CMAKE_CXX_STANDARD 11)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(message SHARED
        bytes_converter.cpp bytes_converter.h
        requests/request.cpp
        replies/reply.cpp)

install(TARGETS message DESTINATION /usr/lib)
install(FILES replies/reply.h requests/request.h DESTINATION include)
