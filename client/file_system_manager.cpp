#include "file_system_manager.h"


int FileSystemManager::open(std::string &file_path, unsigned short mode) {
    if (storage.get_file_descriptor(file_path) != -1)
        throw std::runtime_error("open: can not re-open a file!");
    try {
        client.open_file(mode, file_path);
    } catch (std::runtime_error& err) {
        throw std::runtime_error("open: " + std::string(err.what()));
    }
    File new_file(mode, file_path);
    return storage.add_file(file_path, new_file);
}

void FileSystemManager::close(int desc) {
    auto file_path = storage.desc_to_file_path(desc);
    if (file_path.empty())
        throw std::runtime_error("close: file with descriptor " + std::to_string(desc) + " does not exist!");
//    Waiting for client to support close functionality.
//    try {
//        client.close_file(file_path);
//    } catch (std::runtime_error& err) {
//        throw std::runtime_error("close: " + std::string(err.what()));
//    }
    storage.erase_file(desc);
}




