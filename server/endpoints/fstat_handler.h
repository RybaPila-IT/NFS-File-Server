#ifndef CLIENT_FSTAT_HANDLER_H
#define CLIENT_FSTAT_HANDLER_H

#include <string>
#include "sys/stat.h"
#include "request.h"


class FstatHandler {
    std::string path;
public:
    FstatHandler(FstatRequest fReq);
    std::string get_fstat();
};


#endif //CLIENT_FSTAT_HANDLER_H
