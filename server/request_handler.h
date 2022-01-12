#ifndef NFS_FILE_SERVER_REQUESTHANDLER_H
#define NFS_FILE_SERVER_REQUESTHANDLER_H

#include <string>

#include "Request.h"
#include "access_manager.h"

class request_handler {
private:
    int socket_fd;

    void handle_close(std::string&);
    void handle_connect(std::string&);
    void handle_fstat(std::string&);
    void handle_lseek(std::string&);
    void handle_open(std::string&);
    void handle_read(std::string&);
    void handle_unlink(std::string&);
    void handle_write(std::string&);

public:

    explicit request_handler(int socket_fd);

    void handle_request(std::string&);
};


#endif //NFS_FILE_SERVER_REQUESTHANDLER_H
