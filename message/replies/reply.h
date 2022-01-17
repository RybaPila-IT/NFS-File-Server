#ifndef NFS_FILE_SERVER_REPLY_H
#define NFS_FILE_SERVER_REPLY_H

#include <string>

class ErrorReply {
    const char reply_type;
    std::string error_message;
public:
    ErrorReply();
    ErrorReply(const std::string &errorMsg);
    void deserialize(std::string &val);
    std::string serialize();
    std::string get_error_message();
};

class CloseReply {
    const char reply_type;
public:
    CloseReply();
    void deserialize(std::string &val);
    std::string serialize();
};

class FstatReply {
    const char reply_type;
    std::string file_status;
public:
    FstatReply();
    FstatReply(const std::string &fileStatus);
    void deserialize(std::string &val);
    std::string serialize();
    std::string get_file_status();
};

class OpenReply {
    const char reply_type;
public:
    OpenReply();
    void deserialize(std::string &val);
    std::string serialize();
};

class ReadReply {
    const char reply_type;
    std::string file_content;
public:
    ReadReply();
    ReadReply(const std::string &file_content);
    void deserialize(std::string &val);
    std::string serialize();
    std::string get_file_content();
};

class UnlinkReply {
    const char reply_type;
public:
    UnlinkReply();
    void deserialize(std::string &val);
    std::string serialize();
};

class WriteReply {
    const char reply_type;
public:
    WriteReply();
    void deserialize(std::string &val);
    std::string serialize();
};

#endif //NFS_FILE_SERVER_REPLY_H