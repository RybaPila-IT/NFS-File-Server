#include <iostream>
#include <sys/stat.h>
#include <fstream>

#include "open_file_handler.h"
#include "reply.h"
#include "../access_manager.h"
#include "../logger.h"

#define CREATE 0
#define READ   1
#define WRITE  2
#define READ_WRITE 3

OpenFileHandler::OpenFileHandler(OpenRequest &request) :
        path_to_file(request.get_path()),
        open_mode(request.get_open_mode()) {}

void OpenFileHandler::open_file_in_create_mode() {
    //Create if file doesn't exist
    if (!does_file_exist(path_to_file)) {
        std::ofstream new_file(path_to_file);
        if (!new_file) {
            Logger::get_instance().create_new_log("[OpenFileHandler::open_file_in_create_mode()] Unable to create file: " + path_to_file, std::this_thread::get_id());
            throw std::runtime_error("Unable to create file: " + path_to_file);
        }
        //Open only for file creation - unused further
        new_file.close();
    }

    //Check if file is blocked or add it if it doesn't exist (so it works in every case)
    if (AccessManager::get_instance().is_file_blocked(path_to_file)) {
        Logger::get_instance().create_new_log("[OpenFileHandler::open_file_in_create_mode()] File: " + path_to_file + " is taken by writer", std::this_thread::get_id());
        throw std::runtime_error("File: " + path_to_file + " is taken by writer");
    }
    Logger::get_instance().create_new_log("[OpenFileHandler::open_file_in_create_mode()] Successfully opened file: " + path_to_file + " in create mode", std::this_thread::get_id());
}

void OpenFileHandler::open_file_in_read_mode() {
    check_file_availability();
    Logger::get_instance().create_new_log("[OpenFileHandler::open_file_in_read_mode()] Successfully opened file: " + path_to_file + " in read mode", std::this_thread::get_id());
}

void OpenFileHandler::open_file_in_write_mode() {
    check_file_availability();
    try {
        AccessManager::get_instance().block_file_for_writer(path_to_file);
    }
    catch (std::runtime_error &err) {
        Logger::get_instance().create_new_log("[OpenFileHandler::open_file_in_write_mode()] Cannot open file: " + path_to_file + " in write mode: " + std::string(err.what()), std::this_thread::get_id());
        throw std::runtime_error("Cannot open file: " + path_to_file + " in write mode: " + std::string(err.what()));
    }
    Logger::get_instance().create_new_log("[OpenFileHandler::open_file_in_write_mode()] Successfully opened file: " + path_to_file + " in write mode", std::this_thread::get_id());
}

bool OpenFileHandler::does_file_exist(const std::string &path) {
    struct stat buffer;
    return (stat(path.c_str(), &buffer) == 0);
}

void OpenFileHandler::open_file() {
    std::string error_message = "Open file handler: wrong open mode - received: " + std::to_string(open_mode);
    switch (open_mode) {
        case CREATE:
            open_file_in_create_mode();
            break;
        case READ:
            open_file_in_read_mode();
            break;
        case WRITE:
            open_file_in_write_mode();
            break;
        case READ_WRITE:
            open_file_in_write_mode();
            break;
        default:
            std::cout << error_message << std::endl;
            throw std::runtime_error(error_message);
    }
}

void OpenFileHandler::check_file_availability() {
    if (!does_file_exist(path_to_file)) {
        Logger::get_instance().create_new_log("[OpenFileHandler::check_file_availability()] File: " + path_to_file + " does not exist!", std::this_thread::get_id());
        throw std::runtime_error("File: " + path_to_file + " does not exist!");
    }
    if (AccessManager::get_instance().is_file_blocked(path_to_file)) {
        Logger::get_instance().create_new_log("[OpenFileHandler::check_file_availability()] File: " + path_to_file + " is taken by writer!", std::this_thread::get_id());
        throw std::runtime_error("File: " + path_to_file + " is taken by writer!");
    }
}
