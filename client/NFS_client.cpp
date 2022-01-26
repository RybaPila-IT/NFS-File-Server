#include <stdexcept>

#include "NFS_client.h"
#include "reply.h"
#include "request.h"

NFS_client::NFS_client(const char *server_ip, const int port_number) : socket() {
    try {
        socket.connect_to(server_ip, port_number);
    } catch (std::runtime_error &err) {
        throw std::runtime_error("NFS_client constructor: " + std::string(err.what()));
    }
}

std::string NFS_client::send_request(std::string &request_data) {
    std::string message;
    try {
        socket.write_message(request_data);
        message = socket.read_message();
    } catch (std::runtime_error &err) {
        throw std::runtime_error("NFS_client - send_request: " + std::string(err.what()));
    }
    return message;
}

bool NFS_client::is_reply_error_message(char reply_type) {
    return reply_type == 'E';
}

void NFS_client::handle_error(std::string &reply_data, std::string &func_name) {
    ErrorReply error;
    error.deserialize(reply_data);
    throw std::runtime_error("NFS_client - " + func_name + ": error from server: " + error.get_error_message());
}

void NFS_client::open_file(unsigned short open_mode, std::string &path) {
    OpenRequest request(open_mode, path);
    std::string data = request.serialize();
    std::string reply_data = send_request(data);
    if (is_reply_error_message(reply_data[0])) {
        std::string func_name("close file");
        handle_error(reply_data, func_name);
    }
}

void NFS_client::close_file(std::string &path) {
    CloseRequest request(path);
    std::string data = request.serialize();
    std::string reply_data = send_request(data);
    if (is_reply_error_message(reply_data[0])) {
        std::string func_name("close file");
        handle_error(reply_data, func_name);
    }
}

std::string NFS_client::read_from_file(std::string &path) {
    ReadRequest request(path);
    std::string data = request.serialize();
    std::string reply_data = send_request(data);
    if (is_reply_error_message(reply_data[0])) {
        std::string func_name("read from file");
        handle_error(reply_data, func_name);
    }
    ReadReply reply;
    reply.deserialize(reply_data);
    return reply.get_file_content();
}

void NFS_client::write_to_file(std::string &path, std::string &content) {
    WriteRequest request(path, content);
    std::string data = request.serialize();
    std::string reply_data = send_request(data);
    if (is_reply_error_message(reply_data[0])) {
        std::string func_name("write to file");
        handle_error(reply_data, func_name);
    }
}

std::string NFS_client::get_fstat_info(std::string &path) {
    FstatRequest request(path);
    std::string data = request.serialize();
    std::string reply_data = send_request(data);
    if (is_reply_error_message(reply_data[0])) {
        std::string func_name("fstat");
        handle_error(reply_data, func_name);
    }
    FstatReply reply;
    reply.deserialize(reply_data);
    return reply.get_file_status();
}
