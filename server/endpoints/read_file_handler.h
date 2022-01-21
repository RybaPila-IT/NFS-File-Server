#ifndef SERVER_READ_FILE_HANDLER_H
#define SERVER_READ_FILE_HANDLER_H


#include  <string>
#include  "request.h"


class ReadFileHandler {
    std::string path;
public:
    ReadFileHandler(ReadRequest &request);

    std::string read_file();
};

#endif //SERVER_READ_FILE_HANDLER_H
