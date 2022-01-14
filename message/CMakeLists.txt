cmake_minimum_required(VERSION 3.10.2)
project (message)

set(CMAKE_CXX_STANDARD 11)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(message SHARED
    BytesConverter.cpp
        Requests/request.cpp
    Replies/Reply.cpp
)

install(TARGETS message DESTINATION /usr/lib)
install(FILES
    BytesConverter.h

    Replies/Reply.h
    Replies/ReplyInfo.h

        Requests/request.h
        Requests/request_info.h

    DESTINATION include)
