#ifndef NFS_FILE_SERVER_REQUESTHANDLER_H
#define NFS_FILE_SERVER_REQUESTHANDLER_H
#include "../Message/MessageTypes.h"

class RequestHandler {
    void HandleClose(std::string);
    void HandleConnect(std::string);
    void HandleFstat(std::string);
    void HandleLseek(std::string);
    void HandleOpen(std::string);
    void HandleRead(std::string);
    void HandleUnlink(std::string);
    void HandleWrite(std::string);
};


#endif //NFS_FILE_SERVER_REQUESTHANDLER_H
