#include "request_handler.h"
#include "endpoints/open_file_handler.h"
#include "endpoints/close_file_handler.h"
#include "reply.h"
#include <iostream>

void RequestHandler::handle_close(std::string &message) {
    CloseRequest close_request;
    close_request.deserialize(message);
    try {
        CloseFileHandler close_file_handler(close_request);
        close_file_handler.close_file();
    } catch (std::runtime_error& err) {
        std::string error_mess = std::string(err.what());
        send_error(error_mess);
        return;
    }
    CloseReply reply;
    std::string reply_bytes = reply.serialize();
    send_ok_reply(reply_bytes);
}

void RequestHandler::handle_fstat(std::string &message) {
    std::cout << "HANDLING FSTAT | MSG LENGTH: " << message.length() << std::endl;
    FstatRequest fReq;
    fReq.deserialize(message);
}

void RequestHandler::handle_open(std::string &message) {
    OpenRequest open_request;
    open_request.deserialize(message);
    try {
        OpenFileHandler open_file_handler(open_request);
        open_file_handler.open_file();
    } catch (std::runtime_error& err) {
        std::string error_mess = std::string(err.what());
        send_error(error_mess);
        return;
    }
    OpenReply reply;
    std::string reply_bytes = reply.serialize();
    send_ok_reply(reply_bytes);
}

void RequestHandler::handle_read(std::string &message) {
    std::cout << "HANDLING READ | MSG LENGTH: " << message.length() << std::endl;
    ReadRequest rReq;
    rReq.deserialize(message);
}

void RequestHandler::handle_unlink(std::string &message) {
    std::cout << "HANDLING UNLINK | MSG LENGTH: " << message.length() << std::endl;
    UnlinkRequest uReq;
    uReq.deserialize(message);
}

void RequestHandler::handle_write(std::string &message) {
    std::cout << "HANDLING WRITE | MSG LENGTH: " << message.length() << std::endl;
    WriteRequest wReq;
    wReq.deserialize(message);
}

RequestHandler::RequestHandler(int fd) : socket(fd), socket_fd(fd) {}

void RequestHandler::handle_request(std::string &buffer) {
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


void RequestHandler::handle_incoming_requests() {
    std::string message;
    do {
        try {
            message = socket.read_message();
            if (!message.empty()) {
                handle_request(message);
            }
        } catch (std::runtime_error &err) {
            throw std::runtime_error("server main - handle_session: " + std::string(err.what()));
        }
    } while (!message.empty());
}

void RequestHandler::send_error(std::string &error_info) {
    ErrorReply error(error_info);
    std::string message = error.serialize();
    socket.write_message(message);
}

void RequestHandler::send_ok_reply(std::string& reply) {
    socket.write_message(reply);
}