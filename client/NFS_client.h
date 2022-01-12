#ifndef CLIENT_NFS_CLIENT_H
#define CLIENT_NFS_CLIENT_H

#include "socket.h"

#define BUFFER_SIZE 1024

class NFS_client {
    TcpSocket socket;
    int port_number;
    std::string server_address;

    const int buffer_size = BUFFER_SIZE;

    std::string send_request(std::string &request_data);
    bool is_reply_error_message(std::string &reply_data);
public:
    NFS_client(std::string &server_ip, int port_number);
    void open_file(unsigned short open_mode, std::string &path);
    void tmp_func_handle_session_interactive();
};


#endif //CLIENT_NFS_CLIENT_H
