#include "read_file_handler.h"
#include "../access_manager.h"
#include "../logger.h"
#include <fstream>
#include <sstream>


ReadFileHandler::ReadFileHandler(ReadRequest &request) :
        path(request.get_path()) {}

std::string ReadFileHandler::read_file() {
    try {
        AccessManager::get_instance().lock_file_mutex(path);
    } catch (std::runtime_error &error) {
        Logger::get_instance().create_new_log("[ReadFileHandler::read_file] Error while locking mutex: " + std::string(error.what()), std::this_thread::get_id());
        throw std::runtime_error("ERROR IN: read_file: " + std::string(error.what()));
    }

    std::string content;
    std::stringstream buffer;
    std::ifstream file_to_read;
    file_to_read.open(path);
    if (!file_to_read) {
        AccessManager::get_instance().unlock_file_mutex(path);
        Logger::get_instance().create_new_log("[ReadFileHandler::read_file()] File couldn't be opened", std::this_thread::get_id());
        throw std::runtime_error("ERROR IN: read_file - file couldn't be opened");
    }
    buffer << file_to_read.rdbuf();
    content = buffer.str();

    file_to_read.close();
    Logger::get_instance().create_new_log("[ReadFileHandler::read_file()] Successfully read file: " + path, std::this_thread::get_id());
    AccessManager::get_instance().unlock_file_mutex(path);
    return content;
}