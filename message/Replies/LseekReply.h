#ifndef NFS_FILE_SERVER_LSEEKREPLY_H
#define NFS_FILE_SERVER_LSEEKREPLY_H
#include "Message.h"

class LseekReply : public Message{

public:
    ReplyInfo info;
    int currentPosition;
    LseekReply(int currentPosition) :
        info(ReplyInfo('L', 4)),
        currentPosition(currentPosition) {};
    void Deserialize(std::string val) override;
    std::string Serialize() override;
};


#endif //NFS_FILE_SERVER_LSEEKREPLY_H
