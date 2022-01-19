#include <iostream>
#include <sys/stat.h>
#include <fstream>

#include "open_file_handler.h"
#include "reply.h"
#include "../access_manager.h"

OpenFileHandler::OpenFileHandler(int fd, OpenRequest &request) :
        socket(fd),
        path_to_file(request.get_path()),
        open_mode(request.get_open_mode()) {}

void OpenFileHandler::open_file_in_create_mode() {
    //Create if file doesn't exist
    if (!does_file_exist(path_to_file)) {
        std::ofstream new_file(path_to_file);
        if (!new_file) {
            std::string error_message("Unable to create file: " + path_to_file);
            send_error(error_message);
            std::cout << error_message << std::endl;
            return;
        }
        //Open only for file creation - unused further
        new_file.close();
    }

    //Check if file is blocked or add it if it doesn't exist (so it works in every case)
    if (AccessManager::get_instance().is_file_blocked(path_to_file)) {
        std::string error_message = "File: " + path_to_file + " is taken by writer";
        send_error(error_message);
        std::cout << error_message << std::endl;
        return;
    }
    try {
        AccessManager::get_instance().block_file_for_writer(path_to_file);
    } catch (std::runtime_error &error) {
        std::string error_message = "Cannot open file: " + path_to_file + "in write mode: " + std::string(error.what());
        send_error(error_message);
        std::cout << error_message << std::endl;
        return;
    }
    std::cout << "Successfully opened file: " + path_to_file + " in create more" << std::endl;
    send_ok_status();
}

void OpenFileHandler::open_file_in_read_mode() {
    if (!is_file_available()) {
        // All was handled in is_file_available function
        return;
    }
    std::cout << "Successfully opened file: " + path_to_file + " in read more" << std::endl;
    send_ok_status();
}

void OpenFileHandler::open_file_in_write_mode() {
    if (!is_file_available()) {
        // All was handled in is_file_available function
        return;
    }
    try {
        AccessManager::get_instance().block_file_for_writer(path_to_file);
    }
    catch (std::runtime_error &error) {
        std::string error_message =
                "Cannot open file: " + path_to_file + " in write mode: " + std::string(error.what());
        send_error(error_message);
        std::cout << error_message << std::endl;
        return;
    }
    std::cout << "Successfully opened file: " + path_to_file + " in write mode" << std::endl;
    send_ok_status();
}

bool OpenFileHandler::does_file_exist(const std::string &path) {
    struct stat buffer;
    return (stat(path.c_str(), &buffer) == 0);
}

void OpenFileHandler::open_file() {
    std::string error_message = "Open file handler: wrong open mode - received: " + std::to_string(open_mode);
    switch (open_mode) {
        case 1:
            open_file_in_create_mode();
            break;
        case 2:
            open_file_in_read_mode();
            break;
        case 3:
            open_file_in_write_mode();
            break;
        default:
            std::cout << error_message << std::endl;
            send_error(error_message);
    }
}

bool OpenFileHandler::is_file_available() {
    if (!does_file_exist(path_to_file)) {
        std::string error_message = "File: " + path_to_file + " does not exist";
        send_error(error_message);
        std::cout << error_message << std::endl;
        return false;
    }
    if (AccessManager::get_instance().is_file_blocked((std::string &) path_to_file)) {
        std::string error_message = "File: " + path_to_file + " is taken by writer";
        send_error(error_message);
        std::cout << error_message << std::endl;
        return false;
    }
    return true;
}

void OpenFileHandler::send_error(std::string &error_info) {
    ErrorReply error(error_info);
    std::string message = error.serialize();
    socket.write_message(message);
}

void OpenFileHandler::send_ok_status() {
    OpenReply reply;
    std::string message = reply.serialize();
    socket.write_message(message);
}
