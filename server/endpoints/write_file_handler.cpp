#include "write_file_handler.h"
#include "../access_manager.h"
#include <fstream>

WriteFileHandler::WriteFileHandler(WriteRequest &request):
        path(request.get_path()),
        content(request.get_file_content()) {}

void WriteFileHandler::write_file() {
    try {
        AccessManager::get_instance().wait_to_operate(path);
        AccessManager::get_instance().set_operated_on(path, true);
    } catch (std::runtime_error &error) {
        AccessManager::get_instance().set_operated_on(path, false);
        throw std::runtime_error("ERROR IN: write_file: " + std::string(error.what()));
    }

    std::ofstream file_to_write;
    file_to_write.open(path, std::ios::trunc);
    if (!file_to_write) {
        AccessManager::get_instance().set_operated_on(path, false);
        throw std::runtime_error("ERROR IN: write_file - file couldn't be opened");
    }
    file_to_write << content;
    file_to_write.close();
    AccessManager::get_instance().set_operated_on(path, false);
}

