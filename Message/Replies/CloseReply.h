#ifndef NFS_FILE_SERVER_CLOSEREPLY_H
#define NFS_FILE_SERVER_CLOSEREPLY_H
#include "../Message.h"

class CloseReply : public Message{

public:
    ReplyInfo info;
    CloseReply() : info(ReplyInfo('Q', 0)) {}
    void Deserialize(std::string) override;
    std::string Serialize() override;
};


#endif //NFS_FILE_SERVER_CLOSEREPLY_H
