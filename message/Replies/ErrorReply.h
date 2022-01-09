#ifndef NFS_FILE_SERVER_ERRORREPLY_H
#define NFS_FILE_SERVER_ERRORREPLY_H
#include "../Message.h"

class ErrorReply : public Message{

public:
    ReplyInfo info;
    std::string errorMsg;
    ErrorReply(const std::string &errorMsg) :
        info(ReplyInfo('E', errorMsg.size())),
        errorMsg(errorMsg) {}
    void Deserialize(std::string val) override;
    std::string Serialize () override;
};


#endif //NFS_FILE_SERVER_ERRORREPLY_H
