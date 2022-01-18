#ifndef CLIENT_FILE_SYSTEM_MANAGER_H
#define CLIENT_FILE_SYSTEM_MANAGER_H

#include "storage.h"
#include "NFS_client.h"

class FileSystemManager {

private:
    NFS_client client;
    Storage    storage;

public:

    int  open(std::string& file_path, unsigned short mode);
    int  read(int desc, char* buffer, int bytes_amount);
    void write(int desc, char* buffer, int bytes_amount);
    void lseek(int desc, int offset);
    void close(int desc);
    int  fstat(int desc, char* buffer, int bytes_amount);
};

#endif //CLIENT_FILE_SYSTEM_MANAGER_H
