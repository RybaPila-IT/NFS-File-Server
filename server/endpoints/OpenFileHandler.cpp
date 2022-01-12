#include "OpenFileHandler.h"

OpenFileHandler::OpenFileHandler(AccessManager& man, int fd, OpenRequest& request):
    manager(man), socket_fd(fd) {
    this->path_to_file = request.filePath;
    this->open_mode = request.openMode;
}

void OpenFileHandler::open_file() {
    //Check if file exists
    //Check if file isn't taken by another file
    //Reserve file in access_manager
    //Return info to the client
}
