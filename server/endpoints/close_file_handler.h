#ifndef SERVER_CLOSE_FILE_HANDLER_H
#define SERVER_CLOSE_FILE_HANDLER_H


#include <string>
#include "request.h"


class CloseFileHandler {
    std::string path_to_file;

public:
    CloseFileHandler(CloseRequest &request);

    void close_file();
};


#endif //SERVER_CLOSE_FILE_HANDLER_H
