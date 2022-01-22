#include "fstat_handler.h"

FstatHandler::FstatHandler(FstatRequest fReq): path(fReq.get_path()){
    //fstat(path, buffer);
}

std::string FstatHandler::get_fstat() {
    std::string data;
//extract values from struct stat to std::string
    return data;
}
