#ifndef NFS_FILE_SERVER_OPENREPLY_H
#define NFS_FILE_SERVER_OPENREPLY_H
#include "Message.h"

class OpenReply : public Message{


public:
    ReplyInfo info;
    unsigned int fileDescriptor;
    OpenReply(unsigned int fileDescriptor) :
            info(ReplyInfo('O', 4)),
            fileDescriptor(fileDescriptor) {}
    void Deserialize(std::string val) override;
    std::string Serialize() override;
};


#endif //NFS_FILE_SERVER_OPENREPLY_H
