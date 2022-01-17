#ifndef NFS_FILE_SERVER_OPENFILEHANDLER_H
#define NFS_FILE_SERVER_OPENFILEHANDLER_H

#include <string>
#include "request.h"

class open_file_handler {
private:
    int socket_fd;
    std::string path_to_file;
    unsigned int open_mode;
public:
    open_file_handler(int socket_fd, OpenRequest &request);
    void open_file();
};


#endif //NFS_FILE_SERVER_OPENFILEHANDLER_H
