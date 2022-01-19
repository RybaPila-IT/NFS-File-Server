#ifndef NFS_FILE_SERVER_SERVER_FILE_H
#define NFS_FILE_SERVER_SERVER_FILE_H
#include <string>
#include <fstream>
#include <unistd.h>
#include "AccessManager.h"
#include "request.h"
#include "reply.h"


class ServerFileManager {
    AccessManager manager;
public:
    ServerFileManager();
    ServerFileManager(AccessManager);
    std::string open_file(std::string message);
    std::string read_file(std::string message);
    std::string write_file(std::string message);

};

#endif //NFS_FILE_SERVER_SERVER_FILE_H
