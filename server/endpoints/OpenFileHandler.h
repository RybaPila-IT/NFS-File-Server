#ifndef NFS_FILE_SERVER_OPENFILEHANDLER_H
#define NFS_FILE_SERVER_OPENFILEHANDLER_H

#include <string>
#include "../AccessManager.h"
#include "Request.h"

class OpenFileHandler {
private:
    int socket_fd;
    std::string path_to_file;
    int open_mode;
    AccessManager manager;
public:
    OpenFileHandler(AccessManager&, int, OpenRequest& request);
    void open_file();
};


#endif //NFS_FILE_SERVER_OPENFILEHANDLER_H
