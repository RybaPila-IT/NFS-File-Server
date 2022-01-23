#include "fstat_handler.h"
#include "../access_manager.h"

FstatHandler::FstatHandler(FstatRequest fstat_request) :
        path(fstat_request.get_path()) {}

std::string FstatHandler::get_fstat() {
    std::string stats;
    try {
        AccessManager::get_instance().lock_file_mutex(path);
    } catch (std::runtime_error &error) {
        throw std::runtime_error("ERROR IN: get_fstat: " + std::string(error.what()));
    }
    FILE *file_to_fstat = fopen(path.c_str(), "r");
    if (!file_to_fstat) {
        AccessManager::get_instance().unlock_file_mutex(path);
        throw std::runtime_error("ERROR IN: file_to_fstat - file couldn't be opened");
    }
    load_fstats(stats, file_to_fstat);
    fclose(file_to_fstat);
    AccessManager::get_instance().unlock_file_mutex(path);
    return stats;
}

std::string FstatHandler::load_fstats(std::string &stats, FILE *file_to_fstat) {
    int fd = fileno(file_to_fstat);
    struct stat *buffer;
    fstat(fd, buffer);

    stats += "FSTAT INFO:";
    stats += "\nID OF DEVICE (st_dev): ";
    stats += std::to_string(buffer->st_dev);
    stats += "\nINODE NUMBER (st_ino): ";
    stats += std::to_string(buffer->st_ino);
    stats += "\nPROTECTION (st_mode): ";
    stats += std::to_string(buffer->st_mode);
    stats += "\nTOTAL SIZE IN BYTES (st_size): ";
    stats += std::to_string(buffer->st_size);
    stats += "\nTIME OF LAST ACCESS (st_atime): ";
    stats += std::to_string(buffer->st_atime);
    stats += "\nTIME OF LAST MODIFICATION (st_mtime): ";
    stats += std::to_string(buffer->st_mtime);
    return stats;
}
