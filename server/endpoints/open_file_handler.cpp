#include <iostream>

#include "open_file_handler.h"
#include "../AccessManager.h"

open_file_handler::open_file_handler(int fd, OpenRequest& request):
    socket_fd(fd), path_to_file(request.filePath), open_mode(request.openMode) {

}

void open_file_handler::open_file() {
    //TODO przykładowy kod aby pokazać jak korzystać z access manager
    std::cout << path_to_file << " | " << open_mode << std::endl;
    AccessManager::get_instance().is_file_blocked((std::string &) path_to_file);
    //Check if file exists
    //Check if file isn't taken by another file
    //Reserve file in AccessManager
    //Return info to the client
}