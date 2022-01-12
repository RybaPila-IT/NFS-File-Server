#include <stdexcept>
#include "access_manager.h"

bool access_manager::is_file_blocked(std::string &path) {
    add_file_if_it_does_not_exist(path);
    for(auto & file : files){
        if(file.path.compare(path) == 0){
            if(file.is_open_by_writer.load())
                return false;
            else
                return true;
        }
    }
    //File doesn't exist in access_manager, so something went wrong
    throw std::runtime_error("access manager is_file_blocked: file" + path + " does not exist");
}

void access_manager::block_file_for_writer(std::string &path) {
    for (auto &file: files) {
        if (file.path.compare(path) == 0) {
            if (!file.is_open_by_writer.load()) {
                file.is_open_by_writer.store(true);
                return;
            } else
                //It should be checked earlier whether file is block
                throw std::runtime_error("access manager block_file_for_writer: file" + path + " is already taken");
        }
    }
}

void access_manager::remove_block(std::string &path) {
    for(auto & file : files) {
        if(file.path.compare(path) == 0) {
            file.is_open_by_writer.store(false);
            return;
        }
    }
    //File has to exist at this point - if it does not something went wrong
    throw std::runtime_error("access_manager: file " + path + " does not exist");
}

bool access_manager::is_file_existing_in_files(std::string &path) {
    for(auto & file : files)
        if(file.path.compare(path) == 0)
            return true;
    return false;
}

void access_manager::add_file_if_it_does_not_exist(std::string &path) {
    if(!is_file_existing_in_files(path)){
        files.emplace_back(path);
    }
}

access_manager &access_manager::get_instance() {
    static access_manager instance;
    return instance;
}

File_Guard::File_Guard(std::string &path): path(path) {
    this->is_open_by_writer.store(false);
}

File_Guard::File_Guard(File_Guard &&file): path(file.path) {
    is_open_by_writer.store(false);
}
