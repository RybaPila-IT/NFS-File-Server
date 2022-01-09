#ifndef NFS_FILE_SERVER_WRITEREPLY_H
#define NFS_FILE_SERVER_WRITEREPLY_H
#include "../Message.h"

class WriteReply : public Message{

public:
    ReplyInfo info;
    WriteReply() : info(ReplyInfo('W', 0)) {};
    void Deserialize(std::string val) override;
    std::string Serialize() override;
};


#endif //NFS_FILE_SERVER_WRITEREPLY_H
