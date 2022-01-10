#ifndef NFS_FILE_SERVER_MESSAGE_H
#define NFS_FILE_SERVER_MESSAGE_H
#include "ReplyInfo.h"
#include "RequestInfo.h"
#include "BytesConverter.h"
/*WERSJA POJEDYNCZEJ KLASY DLA WSZYSTKICH WIADOMOŚCI (OBECNIE NIEUŻYWANA)
 * JEST POŁĄCZCZENIEM KLAS REPLY I REQUEST
 * W PLIKACH MAIN I *****HANDLER ZNAJDUJĄ SIĘ KOMENTARZE CO DO WYKORZYSTYWANYCH WERSJI*/
//W CELU UŻYCIA, ODKOMENTOWAĆ ZAWARTOŚĆ Message.h oraz Message.cpp

/*

//REPLIES------------------------------------------

class CloseReply {
public:
    ReplyInfo info;
    CloseReply() : info(ReplyInfo('Q', 0)) {}
    void Deserialize(std::string);
    std::string Serialize();
};

class ConnectReply {
public:
    ReplyInfo info;
    unsigned short portNumber;
    ConnectReply(unsigned short portNumber) :
            info(ReplyInfo('C', 2)),
            portNumber(portNumber) {};
    void Deserialize(std::string val);
    std::string Serialize();
};

class ErrorReply {
public:
    ReplyInfo info;
    std::string errorMsg;
    ErrorReply(const std::string &errorMsg) :
            info(ReplyInfo('E', errorMsg.size())),
            errorMsg(errorMsg) {}
    void Deserialize(std::string val);
    std::string Serialize ();
};

class FstatReply {
public:
    ReplyInfo info;
    std::string fileStatus;
    FstatReply(const std::string &fileStatus) :
            info(ReplyInfo('F', fileStatus.size())),
            fileStatus(fileStatus) {}
    void Deserialize(std::string val);
    std::string Serialize();
};

class LseekReply {
public:
    ReplyInfo info;
    int currentPosition;
    LseekReply(int currentPosition) :
            info(ReplyInfo('L', 4)),
            currentPosition(currentPosition) {};
    void Deserialize(std::string val);
    std::string Serialize();
};

//REQUESTS-----------------------------------------------------------------------------------

class CloseRequest {
public:
    RequestInfo info;
    unsigned int fileDescriptor;
    CloseRequest(unsigned int fileDescriptor) :
            info(RequestInfo('Q', 4)),
            fileDescriptor(fileDescriptor){}
    void Deserialize(std::string val);
    std::string Serialize();
};

class ConnectRequest {
public:
    RequestInfo info;
    ConnectRequest(): info(RequestInfo('C', 0)){};
    void Deserialize(std::string val);
    std::string Serialize();
};

class FstatRequest {
public:
    RequestInfo info;
    unsigned int fileDescriptor;
    FstatRequest(unsigned int fileDescriptor) :
            info(RequestInfo('F', 4)),
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
            info(RequestInfo('L', 8)),
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
            info(RequestInfo('O', 2 + filePath.size())),
            openMode(openMode),
            filePath(filePath) {};
    void Deserialize(std::string val);
    std::string Serialize();
};

class ReadRequest {
public:
    RequestInfo info;
    unsigned int fileDescriptor;
    ReadRequest(unsigned int fileDescriptor) :
            info(RequestInfo('R', 4)),
            fileDescriptor(fileDescriptor) {}
    void Deserialize(std::string val);
    std::string Serialize();
};

class UnlinkRequest {
public:
    RequestInfo info;
    std::string filePath;
    UnlinkRequest(const std::string &filePath) :
            info(RequestInfo('U', filePath.size() )),
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
            info(RequestInfo('W', 4 + fileContent.size())),
            fileDescriptor(fileDescriptor),
            fileContent(fileContent) {}
    void Deserialize(std::string val);
    std::string Serialize();
};

*/

#endif //NFS_FILE_SERVER_MESSAGE_H
