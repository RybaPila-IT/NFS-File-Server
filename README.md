# NFS-Server
#### Authors: Ignacy Gołoś, Radosław Radziukiewicz, Michał Brus, Jan Dzięgiel

Implementation of NFS-like file server with lib and testing program.

## About the project

Our task was to design, implement and test custom server, which was an easier-copy of an NFS file server.
It was supposed to enable the users capatabilities to open, read, write and browse through the content of the files
with lseek operation. Implemented server operates on threads, which handle the sessions and synchronize the access to shared resources.

## How to build and run the project 
#### Requirements: C++, CMake, UNIX OS

You can build whole project with a script:

`./build_all.sh`

The script will compile dynamic libraries (socket, message, client), so it will need **sudo privileges** to put them in /usr/lib directory.

To run the server you can use a script:

`./run_server.sh address_ip port_number`

If you don't pass any parameters it will use **localhost as an IP address and 6941 as a port number**. 
To make the server visible to other computers (outside of localhost) you can pass either 0.0.0.0 or your inner IP address.

To run testing program you can use a script:

`./run_client_test.sh address_ip port_number`

If you don't pass any parameters it will use **localhost as an IP address and 6941 as a port number of the target server.**

## Documentation

The documentation of the project is (unfortunately) available only in Polish version.

## Server

Server has been written in C++ language. It is a fully concurrent server, operating on threads handling 
the users sessions. 

## Client

Client has been written in C++ language. It is a typical example of the **fat-client**. It contains the 
significant part of the logic of the entire system and protocol.

## Socket

As the part of the project, we have created custom implementation of a TCP socket. It is tailored to 
our needs and supports C++ coding mechanisms such as destructors and exceptions handling.

## Test programs

The final part of the project, was to create the test programs checking the behaviour of the client.
We have delivered many tests, which have been splitted into groups based on their testing target.
All tests pass.

