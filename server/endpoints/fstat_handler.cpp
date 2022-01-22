#include "fstat_handler.h"
#include "../access_manager.h"

FstatHandler::FstatHandler(FstatRequest fReq):
    path(fReq.get_path()){}

std::string FstatHandler::get_fstat() {
    std::string data;
    try {
        AccessManager::get_instance().lock_file_mutex(path);
    } catch (std::runtime_error &error) {
        throw std::runtime_error("ERROR IN: read_file: " + std::string(error.what()));
    }
    FILE *file_to_fstat = fopen(path.c_str(), "r");
    if (!file_to_fstat) {
        AccessManager::get_instance().unlock_file_mutex(path);
        throw std::runtime_error("ERROR IN: file_to_fstat - file couldn't be opened");
    }
    int fd = fileno(file_to_fstat);
    struct stat *buffer;
    fstat(fd, buffer);
    //add valuers from buffer to data
    fclose(file_to_fstat);
    AccessManager::get_instance().unlock_file_mutex(path);
    return data;
}
