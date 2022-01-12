#ifndef CLIENT_NFS_CLIENT_H
#define CLIENT_NFS_CLIENT_H

#include "Request.h"
#include "socket.h"

#include "ReplyHandler.h"

#define LOOP_BACK    "127.0.0.1"
#define DEFAULT_PORT 6941
#define BUFFER_SIZE 1024

class NFS_Client {
    TcpSocket socket;
    ReplyHandler reply_handler;
    int port_number = DEFAULT_PORT;
    std::string server_address = LOOP_BACK;

    const int buffer_size = BUFFER_SIZE;

    void handle_session(std::string&);
public:
    NFS_Client();

    void open_file(unsigned short, std::string&);
    void tmp_func_handle_session_interactive();
    //i tak dalej...
};


#endif //CLIENT_NFS_CLIENT_H
