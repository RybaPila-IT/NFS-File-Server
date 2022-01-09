#ifndef NFS_FILE_SERVER_FSTATREQUEST_H
#define NFS_FILE_SERVER_FSTATREQUEST_H
#include "../Message.h"

class FstatRequest : public Message{

public:
    RequestInfo info;
    unsigned int fileDescriptor;
    FstatRequest(unsigned int fileDescriptor) :
        info(RequestInfo('F', 4)),
        fileDescriptor(fileDescriptor) {}
    void Deserialize(std::string val) override;
    std::string Serialize() override;
};


#endif //NFS_FILE_SERVER_FSTATREQUEST_H
