#ifndef NFS_FILE_SERVER_REQUESTHANDLER_H
#define NFS_FILE_SERVER_REQUESTHANDLER_H

#include <string>

#include "Request.h"
#include "AccessManager.h"

class RequestHandler {
private:
    int socket_fd;
    AccessManager access_manager;

    void handle_close(std::string&);
    void handle_connect(std::string&);
    void handle_fstat(std::string&);
    void handle_lseek(std::string&);
    void handle_open(std::string&);
    void handle_read(std::string&);
    void handle_unlink(std::string&);
    void handle_write(std::string&);

public:

    RequestHandler(int, AccessManager&);

    void handle_request(std::string);
};


#endif //NFS_FILE_SERVER_REQUESTHANDLER_H
