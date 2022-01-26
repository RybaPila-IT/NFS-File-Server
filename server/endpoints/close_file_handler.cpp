#include "close_file_handler.h"
#include "../access_manager.h"
#include <iostream>
#include "reply.h"
#include "../logger.h"

CloseFileHandler::CloseFileHandler(CloseRequest &request) :
        path_to_file(request.get_path()) {}

void CloseFileHandler::close_file() {
    try {
        // Although file can be open by reader, remove_block just set lock in false
        // no matter what was the previous state, so it will work in every case
        AccessManager::get_instance().remove_block(path_to_file);
    } catch (std::runtime_error &error) {
        Logger::get_instance().create_new_log("[CloseFileHandler::close_file()] Cannot close file: " + path_to_file + ". Error: " + std::string(error.what()), std::this_thread::get_id());
        throw std::runtime_error("Cannot close file: " + path_to_file + " error: " + std::string(error.what()));
    }
    Logger::get_instance().create_new_log("[CloseFileHandler::close_file()] Successfully closed file: " + path_to_file, std::this_thread::get_id());
    std::cout << "Successfully closed file: " + path_to_file << std::endl;
}
