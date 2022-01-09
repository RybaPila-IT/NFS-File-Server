cmake_minimum_required(VERSION 3.10.2)
project (message)
set(CMAKE_CXX_STANDARD 11)


include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_library(message SHARED 
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
    BytesConverter.cpp
    Message.cpp
)

install(TARGETS message DESTINATION /usr/lib)
install(FILES
    MessageTypes.h
    Requests/CloseRequest.h
    Requests/ConnectRequest.h
    Requests/FstatRequest.h
    Requests/LseekRequest.h
    Requests/OpenRequest.h
    Requests/ReadRequest.h
    Requests/UnlinkRequest.h
    Requests/WriteRequest.h
    Replies/CloseReply.h
    Replies/ConnectReply.h
    Replies/ErrorReply.h
    Replies/FstatReply.h
    Replies/LseekReply.h
    Replies/OpenReply.h
    Replies/ReadReply.h
    Replies/UnlinkReply.h
    Replies/WriteReply.h
    BytesConverter.h
    Message.h
    ReplyInfo.h
    RequestInfo.h
    DESTINATION include)
