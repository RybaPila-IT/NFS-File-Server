#ifndef NFS_FILE_SERVER_REPLYHANDLER_H
#define NFS_FILE_SERVER_REPLYHANDLER_H

#include "Reply.h"

class ReplyHandler {
private:
    void handle_close(std::string&);
    void handle_connect(std::string&);
    void handle_error(std::string&);
    void handle_fstat(std::string&);
    void handle_lseek(std::string&);
    void handle_open(std::string&);
    void handle_read(std::string&);
    void handle_unlink(std::string&);
    void handle_write(std::string&);
public:
    void handle_reply(std::string&);
};


#endif //NFS_FILE_SERVER_REPLYHANDLER_H
