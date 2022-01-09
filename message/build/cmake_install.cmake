# Install script for directory: /home/jan/CLionProjects/NFS-File-Server/message

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/usr/lib/libmessage.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/lib/libmessage.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/lib/libmessage.so"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/lib/libmessage.so")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/lib" TYPE SHARED_LIBRARY FILES "/home/jan/CLionProjects/NFS-File-Server/message/build/libmessage.so")
  if(EXISTS "$ENV{DESTDIR}/usr/lib/libmessage.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/lib/libmessage.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/lib/libmessage.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "/home/jan/CLionProjects/NFS-File-Server/message/MessageTypes.h"
    "/home/jan/CLionProjects/NFS-File-Server/message/Requests/CloseRequest.h"
    "/home/jan/CLionProjects/NFS-File-Server/message/Requests/ConnectRequest.h"
    "/home/jan/CLionProjects/NFS-File-Server/message/Requests/FstatRequest.h"
    "/home/jan/CLionProjects/NFS-File-Server/message/Requests/LseekRequest.h"
    "/home/jan/CLionProjects/NFS-File-Server/message/Requests/OpenRequest.h"
    "/home/jan/CLionProjects/NFS-File-Server/message/Requests/ReadRequest.h"
    "/home/jan/CLionProjects/NFS-File-Server/message/Requests/UnlinkRequest.h"
    "/home/jan/CLionProjects/NFS-File-Server/message/Requests/WriteRequest.h"
    "/home/jan/CLionProjects/NFS-File-Server/message/Replies/CloseReply.h"
    "/home/jan/CLionProjects/NFS-File-Server/message/Replies/ConnectReply.h"
    "/home/jan/CLionProjects/NFS-File-Server/message/Replies/ErrorReply.h"
    "/home/jan/CLionProjects/NFS-File-Server/message/Replies/FstatReply.h"
    "/home/jan/CLionProjects/NFS-File-Server/message/Replies/LseekReply.h"
    "/home/jan/CLionProjects/NFS-File-Server/message/Replies/OpenReply.h"
    "/home/jan/CLionProjects/NFS-File-Server/message/Replies/ReadReply.h"
    "/home/jan/CLionProjects/NFS-File-Server/message/Replies/UnlinkReply.h"
    "/home/jan/CLionProjects/NFS-File-Server/message/Replies/WriteReply.h"
    "/home/jan/CLionProjects/NFS-File-Server/message/BytesConverter.h"
    "/home/jan/CLionProjects/NFS-File-Server/message/Message.h"
    "/home/jan/CLionProjects/NFS-File-Server/message/ReplyInfo.h"
    "/home/jan/CLionProjects/NFS-File-Server/message/RequestInfo.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/jan/CLionProjects/NFS-File-Server/message/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
