#ifndef SERVER_CLOSE_FILE_HANDLER_H
#define SERVER_CLOSE_FILE_HANDLER_H


#include <string>
#include "request.h"
#include "socket.h"

class CloseFileHandler {
    TcpSocket socket;
    std::string path_to_file;
    void send_error(std::string &error_info);
    void send_ok_status();
public:
    CloseFileHandler(int socket_fd, CloseRequest &request);
    void close_file();
};


#endif //SERVER_CLOSE_FILE_HANDLER_H
