#include "request_handler.h"
#include "endpoints/open_file_handler.h"
#include <iostream>

void request_handler::handle_close(std::string& message) {
    CloseRequest qReq = CloseRequest(0);
    qReq.Deserialize(message);
    std::cout << "DE: "<< qReq.info.requestType << "|" << qReq.info.dataSize << std::endl<<std::endl;
}

void request_handler::handle_connect(std::string& message) {
    ConnectRequest cReq = ConnectRequest();
    cReq.Deserialize(message);
    std::cout << "DE: "<< cReq.info.requestType << "|" << cReq.info.dataSize<< std::endl<<std::endl;
}

void request_handler::handle_fstat(std::string& message) {
    FstatRequest fReq = FstatRequest(0);
    fReq.Deserialize(message);
    std::cout << "DE: "<< fReq.info.requestType << "|" << fReq.info.dataSize << "|" <<fReq.fileDescriptor << std::endl<<std::endl;
}

void request_handler::handle_lseek(std::string& message) {
    LseekRequest lReq = LseekRequest(0, 0);
    lReq.Deserialize(message);
    std::cout << "DE: "<< lReq.info.requestType << "|" << lReq.info.dataSize <<"|"<< lReq.fileDescriptor << "|" <<lReq.seekLength<<std::endl<<std::endl;
}

void request_handler::handle_open(std::string& message) {
    OpenRequest open_request = OpenRequest(0,"");
    open_request.Deserialize(message);
    // Finally, request handling with further communication to client
    open_file_handler open_file_handler(socket_fd, open_request);
    open_file_handler.open_file();
}

void request_handler::handle_read(std::string& message) {
    ReadRequest rReq = ReadRequest(0);
    rReq.Deserialize(message);
    std::cout << "DE: "<< rReq.info.requestType << "|" << rReq.info.dataSize <<"|"<< rReq.fileDescriptor <<std::endl<<std::endl;
}

void request_handler::handle_unlink(std::string& message) {
    UnlinkRequest uReq = UnlinkRequest("");
    uReq.Deserialize(message);
    std::cout << "DE: "<< uReq.info.requestType << "|" << uReq.info.dataSize << "|"<< uReq.filePath <<std::endl<<std::endl;
}

void request_handler::handle_write(std::string& message) {
    WriteRequest wReq = WriteRequest(0, "");
    wReq.Deserialize(message);
    std::cout << "PE: "<< wReq.info.requestType << "|" << wReq.info.dataSize << "|"<< wReq.fileDescriptor<<"|"<< wReq.fileContent <<std::endl<<std::endl;
}

request_handler::request_handler(int fd): socket_fd(fd) {}

void request_handler::handle_request(std::string& buffer) {
    switch (buffer[0]) {
        case 'Q':
            handle_close(buffer);
            break;
        case 'C':
            handle_connect(buffer);
            break;
        case 'F':
            handle_fstat(buffer);
            break;
        case 'L':
            handle_lseek(buffer);
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