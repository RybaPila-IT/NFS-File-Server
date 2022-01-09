#ifndef NFS_FILE_SERVER_READREPLY_H
#define NFS_FILE_SERVER_READREPLY_H
#include "../Message.h"

class ReadReply : public Message{


public:
    ReplyInfo info;
    std::string fileContent;
    ReadReply(const std::string &fileContent) :
            info(ReplyInfo('R', fileContent.size())),
            fileContent(fileContent) {}
    void Deserialize(std::string val) override;
    std::string Serialize() override;
};


#endif //NFS_FILE_SERVER_READREPLY_H
