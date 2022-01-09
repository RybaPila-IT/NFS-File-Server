#ifndef NFS_FILE_SERVER_READREQUEST_H
#define NFS_FILE_SERVER_READREQUEST_H
#include "Message.h"

class ReadRequest : public Message{

public:
    RequestInfo info;
    unsigned int fileDescriptor;
    ReadRequest(unsigned int fileDescriptor) :
        info(RequestInfo('R', 4)),
        fileDescriptor(fileDescriptor) {}
    void Deserialize(std::string val) override;
    std::string Serialize() override;
};


#endif //NFS_FILE_SERVER_READREQUEST_H
