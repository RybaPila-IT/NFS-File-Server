#ifndef SERVER_WRITE_FILE_HANDLER_H
#define SERVER_WRITE_FILE_HANDLER_H

#include <string>
#include "request.h"


class WriteFileHandler {
    std::string path;
    std::string content;
public:
    WriteFileHandler(WriteRequest &request);

    void write_file();
};


#endif //SERVER_WRITE_FILE_HANDLER_H
