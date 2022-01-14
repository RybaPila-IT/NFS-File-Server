#ifndef NFS_FILE_SERVER_REPLY_H
#define NFS_FILE_SERVER_REPLY_H

#include "ReplyInfo.h"
#include "BytesConverter.h"

class CloseReply {
public:
    ReplyInfo info;
    CloseReply() : info(ReplyInfo('Q', 1)) {}
    void Deserialize(std::string);
    std::string Serialize();
};

class ConnectReply {
public:
    ReplyInfo info;
    unsigned short portNumber;
    ConnectReply(unsigned short portNumber) :
            info(ReplyInfo('C', 5)),
            portNumber(portNumber) {};
    void Deserialize(std::string val);
    std::string Serialize();
};

class ErrorReply {
public:
    ReplyInfo info;
    std::string errorMsg;
    ErrorReply(const std::string &errorMsg) :
            info(ReplyInfo('E', 1 + errorMsg.size())),
            errorMsg(errorMsg) {}
    void Deserialize(std::string val);
    std::string Serialize ();
};

class FstatReply {
public:
    ReplyInfo info;
    std::string fileStatus;
    FstatReply(const std::string &fileStatus) :
            info(ReplyInfo('F', 1 + fileStatus.size())),
            fileStatus(fileStatus) {}
    void Deserialize(std::string val);
    std::string Serialize();
};

class LseekReply {
public:
    ReplyInfo info;
    int currentPosition;
    LseekReply(int currentPosition) :
            info(ReplyInfo('L', 5)),
            currentPosition(currentPosition) {};
    void Deserialize(std::string val);
    std::string Serialize();
};

class OpenReply {
public:
    ReplyInfo info;
    unsigned int fileDescriptor;
    OpenReply(unsigned int fileDescriptor) :
            info(ReplyInfo('O', 5)),
            fileDescriptor(fileDescriptor) {}
    void Deserialize(std::string val);
    std::string Serialize();
};

class ReadReply {
public:
    ReplyInfo info;
    std::string fileContent;
    ReadReply(const std::string &fileContent) :
            info(ReplyInfo('R', 1 + fileContent.size())),
            fileContent(fileContent) {}
    void Deserialize(std::string val);
    std::string Serialize();
};

class UnlinkReply {
public:
    ReplyInfo info;
    UnlinkReply() : info(ReplyInfo('U', 1)) {}
    void Deserialize(std::string val);
    std::string Serialize();
};

class WriteReply {
public:
    ReplyInfo info;
    WriteReply() : info(ReplyInfo('W', 1)) {};
    void Deserialize(std::string val);
    std::string Serialize();
};

#endif //NFS_FILE_SERVER_REPLY_H
