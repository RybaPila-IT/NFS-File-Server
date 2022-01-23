#ifndef CLIENT_FILE_SYSTEM_MANAGER_H
#define CLIENT_FILE_SYSTEM_MANAGER_H

#include "storage.h"
#include "NFS_client.h"

class FileSystemManager {

private:

    struct FileSystem {
        NFS_client client;
        Storage storage;
    };

    std::unordered_map<std::string, FileSystem> mounted_systems;
    std::unordered_map<std::string, FileSystem>::iterator current_file_system;

    void check_mounted();

public:
    FileSystemManager();

    int  open(std::string& file_path, unsigned short mode);
    int  read(int desc, char* buffer, int bytes_amount);
    void write(int desc, char* buffer, int bytes_amount);
    void lseek(int desc, int offset);
    void close(int desc);
    std::string fstat(int desc);
    void unlink(std::string& file_path);
    void mount(const char *server_ip, int port_number);
};

#endif //CLIENT_FILE_SYSTEM_MANAGER_H
