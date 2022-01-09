#ifndef NFS_FILE_SERVER_OPENREQUEST_H
#define NFS_FILE_SERVER_OPENREQUEST_H
#include "../Message.h"


class OpenRequest : public Message{

public:
    RequestInfo info;
    unsigned short openMode;
    std::string filePath;
    OpenRequest(unsigned short openMode, const std::string &filePath) :
            info(RequestInfo('O', 2 + filePath.size())),
            openMode(openMode),
            filePath(filePath) {};
    void Deserialize(std::string val) override;
    std::string Serialize() override;
};


#endif //NFS_FILE_SERVER_OPENREQUEST_H
