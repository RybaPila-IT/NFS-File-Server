#ifndef NFS_FILE_SERVER_UNLINKREPLY_H
#define NFS_FILE_SERVER_UNLINKREPLY_H
#include "../Message.h"

class UnlinkReply : public Message{

public:
    ReplyInfo info;
    UnlinkReply() : info(ReplyInfo('U', 0)) {}
    void Deserialize(std::string val) override;
    std::string Serialize() override;
};


#endif //NFS_FILE_SERVER_UNLINKREPLY_H
