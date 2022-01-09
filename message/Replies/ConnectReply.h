#ifndef NFS_FILE_SERVER_CONNECTREPLY_H
#define NFS_FILE_SERVER_CONNECTREPLY_H
#include "../Message.h"

class ConnectReply : public Message{


public:
    ReplyInfo info;
    unsigned short portNumber;
    ConnectReply(unsigned short portNumber) :
        info(ReplyInfo('C', 2)),
        portNumber(portNumber) {};
    void Deserialize(std::string val) override;
    std::string Serialize() override;
};


#endif //NFS_FILE_SERVER_CONNECTREPLY_H
