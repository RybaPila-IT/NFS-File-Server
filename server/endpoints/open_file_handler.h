#ifndef NFS_FILE_SERVER_OPENFILEHANDLER_H
#define NFS_FILE_SERVER_OPENFILEHANDLER_H

#include <string>
#include "request.h"
#include "socket.h"

class OpenFileHandler {
private:
    TcpSocket socket;
    std::string path_to_file;
    unsigned int open_mode;

    void open_file_in_create_mode();
    void open_file_in_read_mode();
    void open_file_in_write_mode();

    bool is_file_available();
    bool does_file_exist(const std::string &path);
    void send_error(std::string &error_info);
    void send_ok_status();
public:
    OpenFileHandler(int socket_fd, OpenRequest &request);
    void open_file();
};

#endif //NFS_FILE_SERVER_OPENFILEHANDLER_H
