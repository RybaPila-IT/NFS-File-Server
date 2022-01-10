#ifndef NFS_FILE_SERVER_REPLY_H
#define NFS_FILE_SERVER_REPLY_H
#include "ReplyInfo.h"
#include "BytesConverter.h"

/*WERSJA OSOBNYCH KLAS DLA REPLY I REQUEST (OBECNIE UŻYWANA)
 * W PLIKACH MAIN I *****HANDLER ZNAJDUJĄ SIĘ KOMENTARZE CO DO WYKORZYSTYWANYCH WERSJI*/

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

class OpenReply {
public:
    ReplyInfo info;
    unsigned int fileDescriptor;
    OpenReply(unsigned int fileDescriptor) :
            info(ReplyInfo('O', 4)),
            fileDescriptor(fileDescriptor) {}
    void Deserialize(std::string val);
    std::string Serialize();
};

class ReadReply {
public:
    ReplyInfo info;
    std::string fileContent;
    ReadReply(const std::string &fileContent) :
            info(ReplyInfo('R', fileContent.size())),
            fileContent(fileContent) {}
    void Deserialize(std::string val);
    std::string Serialize();
};

class UnlinkReply {
public:
    ReplyInfo info;
    UnlinkReply() : info(ReplyInfo('U', 0)) {}
    void Deserialize(std::string val);
    std::string Serialize();
};

class WriteReply {
public:
    ReplyInfo info;
    WriteReply() : info(ReplyInfo('W', 0)) {};
    void Deserialize(std::string val);
    std::string Serialize();
};

#endif //NFS_FILE_SERVER_REPLY_H
