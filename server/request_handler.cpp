#include "request_handler.h"
#include "endpoints/open_file_handler.h"
#include <iostream>

void request_handler::handle_close(std::string& message) {
    std::cout << "HANDLING CLOSE | MSG LENGTH: " << message.length() <<std::endl;
    CloseRequest qReq;
    qReq.deserialize(message);
}

void request_handler::handle_fstat(std::string& message) {
    std::cout << "HANDLING FSTAT | MSG LENGTH: " << message.length() <<std::endl;
    FstatRequest fReq;
    fReq.deserialize(message);
}

void request_handler::handle_open(std::string& message) {
    std::cout << "HANDLING OPEN | MSG LENGTH: " << message.length() <<std::endl;
    OpenRequest open_request;
    open_request.deserialize(message);
    // Finally, request handling with further communication to client
    open_file_handler open_file_handler(socket_fd, open_request);
    open_file_handler.open_file();
}

void request_handler::handle_read(std::string& message) {
    std::cout << "HANDLING READ | MSG LENGTH: " << message.length() <<std::endl;
    ReadRequest rReq;
    rReq.deserialize(message);
}

void request_handler::handle_unlink(std::string& message) {
    std::cout << "HANDLING UNLINK | MSG LENGTH: " << message.length() <<std::endl;
    UnlinkRequest uReq;
    uReq.deserialize(message);
}

void request_handler::handle_write(std::string& message) {
    std::cout << "HANDLING WRITE | MSG LENGTH: " << message.length() <<std::endl;
    WriteRequest wReq;
    wReq.deserialize(message);
}

request_handler::request_handler(int fd): socket_fd(fd) {}

void request_handler::handle_request(std::string& buffer) {
    switch (buffer[0]) {
        case 'Q':
            handle_close(buffer);
            break;
        case 'F':
            handle_fstat(buffer);
            break;
        case 'O':
            handle_open(buffer);
            break;
        case 'R':
            handle_read(buffer);
            break;
        case 'U':
            handle_unlink(buffer);
            break;
        case 'W':
            handle_write(buffer);
            break;
        default:
            throw std::runtime_error("request handler: unrecognized type of the message");
    }
}