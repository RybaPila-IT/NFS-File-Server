#include <stdexcept>
#include "AccessManager.h"

bool AccessManager::is_file_blocked(std::string &path) {
    add_file_if_it_does_not_exist(path);
    auto file = files.find(path);
    if (file != files.end())
        return file->second.is_open_by_writer();
    else
        //File doesn't exist in AccessManager, so something went wrong
        throw std::runtime_error("AccessManager is_file_blocked: file " + path + " does not exist");
}

void AccessManager::block_file_for_writer(std::string &path) {
    auto file = files.find(path);
    if (file != files.end()) {
        if(!file->second.is_open_by_writer())
            file->second.set_lock(true);
        else
            //It should be checked earlier whether file is block
            throw std::runtime_error("AccessManager block_file_for_writer: file " + path + " is already taken");
    }
    else
        throw std::runtime_error("AccessManager block_file_for_writer: file " + path + " does not exist");
}

void AccessManager::remove_block(std::string &path) {
    auto file = files.find(path);
    if (file != files.end())
        file->second.set_lock(false);
    else
        //File has to exist at this point - if it does not something went wrong
        throw std::runtime_error("AccessManager: file " + path + " does not exist");
}

bool AccessManager::is_file_existing_in_files(std::string &path) {
    auto file = files.find(path);
    if (file != files.end())
        return true;
    else
        return false;
}

void AccessManager::add_file_if_it_does_not_exist(std::string &path) {
    if(!is_file_existing_in_files(path)){
        files.emplace(std::make_pair(path, FileGuard()));
    }
}

AccessManager &AccessManager::get_instance() {
    static AccessManager instance;
    return instance;
}

FileGuard::FileGuard() {
    this->is_open_by_writer_lock.store(false);
}

FileGuard::FileGuard(FileGuard &&file) {
    is_open_by_writer_lock.store(false);
}

bool FileGuard::is_open_by_writer() {
    return is_open_by_writer_lock.load();
}

void FileGuard::set_lock(bool val) {
    is_open_by_writer_lock.store(val);
}
