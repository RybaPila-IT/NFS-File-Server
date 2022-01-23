#ifndef CLIENT_FSTAT_HANDLER_H
#define CLIENT_FSTAT_HANDLER_H

#include <string>
#include "sys/stat.h"
#include "request.h"


class FstatHandler {
private:
    std::string path;
    std::string load_fstats(std::string &stats, FILE *file_to_fstat);
public:
    FstatHandler(FstatRequest fReq);
    std::string get_fstat();
};


#endif //CLIENT_FSTAT_HANDLER_H
