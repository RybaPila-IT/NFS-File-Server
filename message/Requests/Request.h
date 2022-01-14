#ifndef NFS_FILE_SERVER_REQUEST_H
#define NFS_FILE_SERVER_REQUEST_H
#include "RequestInfo.h"
#include "BytesConverter.h"

/*WERSJA OSOBNYCH KLAS DLA REPLY I REQUEST (OBECNIE UŻYWANA)
 * W PLIKACH MAIN I *****HANDLER ZNAJDUJĄ SIĘ KOMENTARZE CO DO WYKORZYSTYWANYCH WERSJI*/

class CloseRequest {
public:
    RequestInfo info;
    unsigned int fileDescriptor;
    CloseRequest(unsigned int fileDescriptor) :
            info(RequestInfo('Q', 5)),
            fileDescriptor(fileDescriptor){}
    void Deserialize(std::string val);
    std::string Serialize();
};

class ConnectRequest {
public:
    RequestInfo info;
    ConnectRequest(): info(RequestInfo('C', 1)){};
    void Deserialize(std::string val);
    std::string Serialize();
};

class FstatRequest {
public:
    RequestInfo info;
    unsigned int fileDescriptor;
    FstatRequest(unsigned int fileDescriptor) :
            info(RequestInfo('F', 5)),
            fileDescriptor(fileDescriptor) {}
    void Deserialize(std::string val);
    std::string Serialize();
};

class LseekRequest {
public:
    RequestInfo info;
    unsigned int fileDescriptor;
    int seekLength;
    LseekRequest(unsigned int fileDescriptor, int seekLength) :
            info(RequestInfo('L', 9)),
            fileDescriptor(fileDescriptor),
            seekLength(seekLength) {}
    void Deserialize(std::string val);
    std::string Serialize();
};

class OpenRequest {
public:
    RequestInfo info;
    unsigned short openMode;
    std::string filePath;
    OpenRequest(unsigned short openMode, const std::string &filePath) :
            info(RequestInfo('O', 5 + filePath.size())),
            openMode(openMode),
            filePath(filePath) {}
    void Deserialize(std::string val);
    std::string Serialize();
};

class ReadRequest {
public:
    RequestInfo info;
    unsigned int fileDescriptor;
    ReadRequest(unsigned int fileDescriptor) :
            info(RequestInfo('R', 5)),
            fileDescriptor(fileDescriptor) {}
    void Deserialize(std::string val);
    std::string Serialize();
};

class UnlinkRequest {
public:
    RequestInfo info;
    std::string filePath;
    UnlinkRequest(const std::string &filePath) :
            info(RequestInfo('U', 1 + filePath.size() )),
            filePath(filePath) {}
    void Deserialize(std::string val);
    std::string Serialize();
};

class WriteRequest {
public:
    RequestInfo info;
    unsigned int fileDescriptor;
    std::string fileContent;
    WriteRequest(unsigned int fileDescriptor, const std::string &fileContent) :
            info(RequestInfo('W', 5 + fileContent.size())),
            fileDescriptor(fileDescriptor),
            fileContent(fileContent) {}
    void Deserialize(std::string val);
    std::string Serialize();
};

#endif //NFS_FILE_SERVER_REQUEST_H
