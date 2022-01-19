#ifndef NFS_FILE_SERVER_REQUESTHANDLER_H
#define NFS_FILE_SERVER_REQUESTHANDLER_H

#include <string>

#include "socket.h"
#include "request.h"

class RequestHandler {
private:
    int socket_fd;
    TcpSocket socket;

    void handle_request(std::string&);
    void handle_close(std::string&);
    void handle_fstat(std::string&);
    void handle_open(std::string&);
    void handle_read(std::string&);
    void handle_unlink(std::string&);
    void handle_write(std::string&);

    void send_error(std::string&);
    void send_ok_reply(std::string&);

public:
    explicit RequestHandler(int socket_fd);

    void handle_incoming_requests();
};


#endif //NFS_FILE_SERVER_REQUESTHANDLER_H
