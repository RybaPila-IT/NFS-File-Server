#ifndef NFS_FILE_SERVER_UNLINKREQUEST_H
#define NFS_FILE_SERVER_UNLINKREQUEST_H
#include "Message.h"

class UnlinkRequest : public Message{

public:
    RequestInfo info;
    std::string filePath;
    UnlinkRequest(const std::string &filePath) :
        info(RequestInfo('U', filePath.size() )),
        filePath(filePath) {}
    void Deserialize(std::string val) override;
    std::string Serialize() override;
};


#endif //NFS_FILE_SERVER_UNLINKREQUEST_H
