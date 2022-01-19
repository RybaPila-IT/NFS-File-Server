#ifndef NFS_FILE_SERVER_OPENFILEHANDLER_H
#define NFS_FILE_SERVER_OPENFILEHANDLER_H

#include <string>
#include "request.h"
#include "socket.h"

class OpenFileHandler {
private:
    std::string path_to_file;
    unsigned int open_mode;

    void open_file_in_create_mode();
    void open_file_in_read_mode();
    void open_file_in_write_mode();

    void check_file_availability();
    bool does_file_exist(const std::string &path);

public:
    OpenFileHandler(OpenRequest &request);
    void open_file();
};

#endif //NFS_FILE_SERVER_OPENFILEHANDLER_H
