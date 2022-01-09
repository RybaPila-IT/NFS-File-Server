#ifndef NFS_FILE_SERVER_FSTATREPLY_H
#define NFS_FILE_SERVER_FSTATREPLY_H
#include "Message.h"

class FstatReply : public Message{

public:
    ReplyInfo info;
    std::string fileStatus;
    FstatReply(const std::string &fileStatus) :
        info(ReplyInfo('F', fileStatus.size())),
        fileStatus(fileStatus) {}
    void Deserialize(std::string val) override;
    std::string Serialize() override;
};


#endif //NFS_FILE_SERVER_FSTATREPLY_H
