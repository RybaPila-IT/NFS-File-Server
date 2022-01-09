cmake_minimum_required(VERSION 3.10.2)
project (message)
set(CMAKE_CXX_STANDARD 11)


include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/Replies ${CMAKE_CURRENT_SOURCE_DIR}/Requests)
add_library(message SHARED 
    BytesConverter.cpp
    Message.cpp
    Requests/CloseRequest.cpp
    Requests/ConnectRequest.cpp
    Requests/FstatRequest.cpp
    Requests/LseekRequest.cpp
    Requests/OpenRequest.cpp
    Requests/ReadRequest.cpp
    Requests/UnlinkRequest.cpp
    Requests/WriteRequest.cpp
    Replies/CloseReply.cpp
    Replies/ConnectReply.cpp
    Replies/ErrorReply.cpp
    Replies/FstatReply.cpp
    Replies/LseekReply.cpp
    Replies/OpenReply.cpp
    Replies/ReadReply.cpp
    Replies/UnlinkReply.cpp
    Replies/WriteReply.cpp
)

install(TARGETS message DESTINATION /usr/lib)
install(FILES MessageTypes.h DESTINATION include)
