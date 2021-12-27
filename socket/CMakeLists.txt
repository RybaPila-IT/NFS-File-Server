cmake_minimum_required(VERSION 3.10.2)
project (socket)
set(CMAKE_CXX_STANDARD 11)


include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_library(socket SHARED socket.cpp)

install(TARGETS socket DESTINATION /usr/lib)
install(FILES socket.h DESTINATION include)
