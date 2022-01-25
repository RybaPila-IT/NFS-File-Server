#include <cstring>
#include <stdexcept>
#include <iostream>
#include "file_system_manager.h"

#define LOOP_BACK    "127.0.0.1"
#define DEFAULT_PORT 6941

#define CREATE 0
#define READ   1
#define WRITE  2
#define READ_WRITE 3


FileSystemManager::FileSystemManager() : mounted_systems(), current_file_system(mounted_systems.end()) {}

void FileSystemManager::check_mounted() {
    if (current_file_system == mounted_systems.end())
        throw std::runtime_error("No file system is mounted!");
}

int FileSystemManager::open(std::string &file_path, unsigned short mode) {
    check_mounted();
    if (current_file_system->second.storage.get_file_descriptor(file_path) != -1)
        throw std::runtime_error("open: can not re-open a file!");
    try {
        current_file_system->second.client.open_file(mode, file_path);
    } catch (std::runtime_error &err) {
        throw std::runtime_error("open: " + std::string(err.what()));
    }
    File new_file(mode, file_path);
    return current_file_system->second.storage.add_file(file_path, new_file);
}

void FileSystemManager::close(int desc) {
    check_mounted();
    auto file_path = current_file_system->second.storage.desc_to_file_path(desc);
    if (file_path.empty())
        throw std::runtime_error("close: file with descriptor " + std::to_string(desc) + " does not exist!");
    try {
        current_file_system->second.client.close_file(file_path);
    } catch (std::runtime_error &err) {
        throw std::runtime_error("close: " + std::string(err.what()));
    }
    current_file_system->second.storage.erase_file(desc);
}

int FileSystemManager::read(int desc, char *buffer, int bytes_amount) {
    check_mounted();
    std::string read_data;
    try {
        auto file = current_file_system->second.storage.obtain_file(desc);
        if (file.get_mode() != READ && file.get_mode() != READ_WRITE)
            throw std::runtime_error("File with descriptor " + std::to_string(desc) + " is opened in wrong mode!");
        if (!file.is_fetched()) {
            auto file_path = current_file_system->second.storage.desc_to_file_path(desc);
            auto content = current_file_system->second.client.read_from_file(file_path);
            current_file_system->second.storage.set_file_content(desc, content);
            file.set_content(content);
        }
        read_data = file.read(bytes_amount);
        memcpy(buffer, read_data.data(), read_data.size() * sizeof(char));
    } catch (std::runtime_error &err) {
        throw std::runtime_error("read: " + std::string(err.what()));
    }
    return read_data.size();
}

void FileSystemManager::write(int desc, const char *buffer, int bytes_amount) {
    check_mounted();
    std::string write_bytes(buffer, bytes_amount);
    try {
        auto file = current_file_system->second.storage.obtain_file(desc);
        if (file.get_mode() != WRITE && file.get_mode() != READ_WRITE)
            throw std::runtime_error("File with descriptor " + std::to_string(desc) + " is opened in wrong mode!");
        auto new_file_content = file.write_result(write_bytes);
        auto file_path = current_file_system->second.storage.desc_to_file_path(desc);
        current_file_system->second.client.write_to_file(file_path, new_file_content);
        current_file_system->second.storage.set_file_content(desc, new_file_content);
    } catch (std::runtime_error &err) {
        throw std::runtime_error("read: " + std::string(err.what()));
    }
}

void FileSystemManager::lseek(int desc, int offset) {
    check_mounted();
    try {
      current_file_system->second.storage.inc_file_position(desc, offset);
    } catch (std::runtime_error& err) {
        throw std::runtime_error("lseek: " + std::string(err.what()));
    }
}

std::string FileSystemManager::fstat(int desc) {
    check_mounted();
    std::string file_stats;
    auto file_path = current_file_system->second.storage.desc_to_file_path(desc);
    if (file_path.empty())
        throw std::runtime_error("fstat: file with descriptor " + std::to_string(desc) + " does not exist!");
    try {
        file_stats = current_file_system->second.client.get_fstat_info(file_path);
    } catch (std::runtime_error &err) {
        throw std::runtime_error("fstat: " + std::string(err.what()));
    }
    return file_stats;
}
void FileSystemManager::unlink(std::string &file_path) {
    check_mounted();
    auto file_desc = current_file_system->second.storage.get_file_descriptor(file_path);
    if (file_desc == -1)
        throw std::runtime_error("File specified with path " + file_path + " does not exist!");
    close(file_desc);
}

void FileSystemManager::mount(const char *server_ip, int port_number) {
    std::string ip_key = std::string(server_ip) + ":" + std::to_string(port_number);
    if (mounted_systems.find(ip_key) == mounted_systems.end()) {
        try {
            mounted_systems.insert(std::make_pair(ip_key, FileSystem({NFS_client(server_ip, port_number), Storage()})));
        } catch (std::runtime_error& err) {
            throw std::runtime_error("mount: " + std::string(err.what()));
        }
    }
    current_file_system = mounted_systems.find(ip_key);

}
