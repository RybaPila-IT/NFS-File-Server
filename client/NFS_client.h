#ifndef CLIENT_NFS_CLIENT_H
#define CLIENT_NFS_CLIENT_H

#include "socket.h"

#define BUFFER_SIZE 1024

class NFS_client {
    TcpSocket socket;

    const int buffer_size = BUFFER_SIZE;

    std::string send_request(std::string &request_data);
    bool is_reply_error_message(char reply_type);
    void handle_error(std::string &reply_data, std::string &func_name);
public:
    NFS_client(const char *server_ip, int port_number);
    void open_file(unsigned short open_mode, std::string &path);
    void close_file(std::string &path);
    std::string read_from_file(std::string &path);
    void write_to_file(std::string &path, std::string &content);
    std::string get_fstat_info(std::string &path);
};

#endif //CLIENT_NFS_CLIENT_H
