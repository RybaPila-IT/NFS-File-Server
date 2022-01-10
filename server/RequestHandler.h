#ifndef NFS_FILE_SERVER_REQUESTHANDLER_H
#define NFS_FILE_SERVER_REQUESTHANDLER_H
//Jeżeli korzystamy wersji z pojedynczej klasy message - usunąć linijkę poniżej
#include "Request.h"
//Jeżeli korzystamy wersji z pojedynczej klasy message - odkomentować linijkę poniżej
//#include "Message.h"

class RequestHandler {

public:
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
