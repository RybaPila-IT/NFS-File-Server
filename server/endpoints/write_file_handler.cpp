#include <fstream>
#include "write_file_handler.h"
#include "../access_manager.h"
#include "../logger.h"

WriteFileHandler::WriteFileHandler(WriteRequest &request) :
        path(request.get_path()),
        content(request.get_file_content()) {}

void WriteFileHandler::write_file() {
    try {
        AccessManager::get_instance().lock_file_mutex(path);
    } catch (std::runtime_error &error) {
        Logger::get_instance().create_new_log("[WriteFileHandler::write_file()] Error while locking mutex: " + std::string(error.what()), std::this_thread::get_id());
        throw std::runtime_error("ERROR IN: write_file: " + std::string(error.what()));
    }

    std::ofstream file_to_write;
    file_to_write.open(path, std::ios::trunc);
    if (!file_to_write) {
        AccessManager::get_instance().unlock_file_mutex(path);
        Logger::get_instance().create_new_log("[WriteFileHandler::write_file()] File: " + path + "couldn't be opened.", std::this_thread::get_id());
        throw std::runtime_error("ERROR IN: write_file - file couldn't be opened");
    }
    file_to_write << content;
    file_to_write.close();
    AccessManager::get_instance().unlock_file_mutex(path);
}

