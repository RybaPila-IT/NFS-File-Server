#include <cstring>
#include "file_system_manager.h"

#define LOOP_BACK    "127.0.0.1"
#define DEFAULT_PORT 6941

#define CREATE 0
#define READ   1
#define WRITE  2
#define READ_WRITE 3


FileSystemManager::FileSystemManager() : client(LOOP_BACK, DEFAULT_PORT), storage() {}

FileSystemManager::FileSystemManager(const char *server_ip, int port_number) : client(server_ip, port_number),
                                                                               storage() {}

int FileSystemManager::open(std::string &file_path, unsigned short mode) {
    if (storage.get_file_descriptor(file_path) != -1)
        throw std::runtime_error("open: can not re-open a file!");
    try {
        client.open_file(mode, file_path);
    } catch (std::runtime_error &err) {
        throw std::runtime_error("open: " + std::string(err.what()));
    }
    File new_file(mode, file_path);
    return storage.add_file(file_path, new_file);
}

void FileSystemManager::close(int desc) {
    auto file_path = storage.desc_to_file_path(desc);
    if (file_path.empty())
        throw std::runtime_error("close: file with descriptor " + std::to_string(desc) + " does not exist!");
    try {
        client.close_file(file_path);
    } catch (std::runtime_error &err) {
        throw std::runtime_error("close: " + std::string(err.what()));
    }
    storage.erase_file(desc);
}


int FileSystemManager::read(int desc, char *buffer, int bytes_amount) {
    std::string read_data;
    try {
        auto file = storage.obtain_file(desc);
        if (file.get_mode() != READ && file.get_mode() != READ_WRITE)
            throw std::runtime_error("File with descriptor " + std::to_string(desc) + " is opened in wrong mode!");
        if (!file.is_fetched()) {
            auto file_path = storage.desc_to_file_path(desc);
            auto content = client.read_from_file(file_path);
            storage.set_file_content(desc, content);
            file.set_content(content);
        }
        read_data = file.read(bytes_amount);
        memcpy(buffer, read_data.data(), read_data.size() * sizeof(char));
    } catch (std::runtime_error &err) {
        throw std::runtime_error("read: " + std::string(err.what()));
    }
    return read_data.size();
}


void FileSystemManager::write(int desc, char *buffer, int bytes_amount) {
    std::string write_bytes(buffer, bytes_amount);
    try {
        auto file = storage.obtain_file(desc);
        if (file.get_mode() != WRITE && file.get_mode() != READ_WRITE)
            throw std::runtime_error("File with descriptor " + std::to_string(desc) + " is opened in wrong mode!");
        auto file_path = storage.desc_to_file_path(desc);
        client.write_to_file(file_path, write_bytes);
        storage.set_file_content(desc, write_bytes);
    } catch (std::runtime_error &err) {
        throw std::runtime_error("read: " + std::string(err.what()));
    }
}

void FileSystemManager::lseek(int desc, int offset) {


}







