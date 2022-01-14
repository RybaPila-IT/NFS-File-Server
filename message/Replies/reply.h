#ifndef NFS_FILE_SERVER_REPLY_H
#define NFS_FILE_SERVER_REPLY_H

#include <string>

class ErrorReply {
    const char reply_type;
    std::string error_message;
public:
    ErrorReply();
    ErrorReply(const std::string &errorMsg);
    void Deserialize(std::string &val);
    std::string Serialize();
};

class CloseReply {
    const char reply_type;
public:
    CloseReply();
    void Deserialize(std::string &val);
    std::string Serialize();
};

class ConnectReply {
    const char reply_type;
    unsigned short port_number;
public:
    ConnectReply();
    ConnectReply(unsigned short portNumber);
    void Deserialize(std::string &val);
    std::string Serialize();
};

class FstatReply {
    const char reply_type;
    std::string file_status;
public:
    FstatReply();
    FstatReply(const std::string &fileStatus);
    void Deserialize(std::string &val);
    std::string Serialize();
};

class LseekReply {
    const char reply_type;
    int current_position;
public:
    LseekReply();
    LseekReply(int current_position);
    void Deserialize(std::string &val);
    std::string Serialize();
};

class OpenReply {
    const char reply_type;
    unsigned int file_descriptor;
public:
    OpenReply();
    OpenReply(unsigned int file_descriptor);
    void Deserialize(std::string &val);
    std::string Serialize();
};

class ReadReply {
    const char reply_type;
    std::string file_content;
public:
    ReadReply();
    ReadReply(const std::string &file_content);
    void Deserialize(std::string &val);
    std::string Serialize();
};

class UnlinkReply {
    const char reply_type;
public:
    UnlinkReply();
    void Deserialize(std::string &val);
    std::string Serialize();
};

class WriteReply {
    const char reply_type;
public:
    WriteReply();
    void Deserialize(std::string &val);
    std::string Serialize();
};

#endif //NFS_FILE_SERVER_REPLY_H