#ifndef CLIENT_FILE_SYSTEM_MANAGER_H
#define CLIENT_FILE_SYSTEM_MANAGER_H

#include "storage.h"
#include "NFS_client.h"

class FileSystemManager {

private:
    NFS_client client;
    Storage    storage;

public:
    FileSystemManager(const char *server_ip, int port_number);
    FileSystemManager();

    int  open(std::string& file_path, unsigned short mode);
    int  read(int desc, char* buffer, int bytes_amount);
    void write(int desc, char* buffer, int bytes_amount);
    void lseek(int desc, int offset);
    void close(int desc);
    void unlink(std::string& file_path);
    int  fstat(int desc, char* buffer, int bytes_amount);
};

#endif //CLIENT_FILE_SYSTEM_MANAGER_H
