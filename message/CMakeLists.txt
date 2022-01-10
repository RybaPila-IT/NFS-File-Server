cmake_minimum_required(VERSION 3.10.2)
project (message)
set(CMAKE_CXX_STANDARD 11)


include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_library(message SHARED
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
