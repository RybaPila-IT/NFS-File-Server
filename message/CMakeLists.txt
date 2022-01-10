cmake_minimum_required(VERSION 3.10.2)
project (message)

set(CMAKE_CXX_STANDARD 11)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(message SHARED
    BytesConverter.cpp   
    Requests/Request.cpp
    Replies/Reply.cpp
)

install(TARGETS message DESTINATION /usr/lib)
install(FILES
    BytesConverter.h

    Replies/Reply.h
    Replies/ReplyInfo.h

    Requests/Request.h
    Requests/RequestInfo.h

    DESTINATION include)
