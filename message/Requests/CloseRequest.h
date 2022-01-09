#ifndef NFS_FILE_SERVER_CLOSEREQUEST_H
#define NFS_FILE_SERVER_CLOSEREQUEST_H
#include "../Message.h"

class CloseRequest : public Message{

public:
    RequestInfo info;
    unsigned int fileDescriptor;
    CloseRequest(unsigned int fileDescriptor) :
        info(RequestInfo('Q', 4)),
        fileDescriptor(fileDescriptor){}
    void Deserialize(std::string val) override;
    std::string Serialize() override;
};


#endif //NFS_FILE_SERVER_CLOSEREQUEST_H
