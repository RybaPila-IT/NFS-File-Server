#include <iostream>
#include "fstat_handler.h"
#include "../access_manager.h"
#include "../logger.h"

FstatHandler::FstatHandler(FstatRequest &fstat_request) :
        path(fstat_request.get_path()) {}

std::string FstatHandler::get_fstat() {
    std::string styled_fstat_info;
    try {
        AccessManager::get_instance().lock_file_mutex(path);
    } catch (std::runtime_error &error) {
        Logger::get_instance().create_new_log("[FstatHandler::get_fstat()] Error while locking mutex: " + std::string (error.what()), std::this_thread::get_id());
        throw std::runtime_error("ERROR IN: get_fstat: " + std::string(error.what()));
    }
    FILE *file_to_fstat = fopen(path.c_str(), "r");
    if (!file_to_fstat) {
        AccessManager::get_instance().unlock_file_mutex(path);
        Logger::get_instance().create_new_log("[FstatHandler::get_fstat()] File: " + path + "couldn't be opened", std::this_thread::get_id());
        throw std::runtime_error("ERROR IN: file_to_fstat - file couldn't be opened");
    }
    try {
        load_fstats(styled_fstat_info, file_to_fstat);
    }
    catch (std::runtime_error &error) {
        Logger::get_instance().create_new_log("[FstatHandler::get_fstat()] Error while loading fstats to string", std::this_thread::get_id());
        throw std::runtime_error("ERROR IN: load_fstats: " + std::string(error.what()));
    }
    fclose(file_to_fstat);
    Logger::get_instance().create_new_log("[FstatHandler::get_fstat()] Successfully collected fstat info", std::this_thread::get_id());
    std::cout << "Successfully collected fstat info" << std::endl;
    AccessManager::get_instance().unlock_file_mutex(path);
    return styled_fstat_info;
}

std::string FstatHandler::load_fstats(std::string &stats, FILE *file_to_fstat) {
    int fd = fileno(file_to_fstat);
    struct stat buffer;
    if(fstat(fd, &buffer) != 0)
        throw std::runtime_error("ERROR IN: system fstat - couldn't load fstat to buffer");
    stats += "FSTAT INFO:";
    stats += "\nID OF DEVICE (st_dev): ";
    stats += std::to_string(buffer.st_dev);
    stats += "\nINODE NUMBER (st_ino): ";
    stats += std::to_string(buffer.st_ino);
    stats += "\nPROTECTION (st_mode): ";
    stats += std::to_string(buffer.st_mode);
    stats += "\nTOTAL SIZE IN BYTES (st_size): ";
    stats += std::to_string(buffer.st_size);
    stats += "\nTIME OF LAST ACCESS (st_atime): ";
    stats += std::to_string(buffer.st_atime);
    stats += "\nTIME OF LAST MODIFICATION (st_mtime): ";
    stats += std::to_string(buffer.st_mtime);
    std::cout << "Successfully loaded statistics of " + path + " file." << std::endl;
    return stats;
}
