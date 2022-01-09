#ifndef NFS_FILE_SERVER_WRITEREQUEST_H
#define NFS_FILE_SERVER_WRITEREQUEST_H
#include "../Message.h"

class WriteRequest : public Message{

public:
    RequestInfo info;
    unsigned int fileDescriptor;
    std::string fileContent;
    WriteRequest(unsigned int fileDescriptor, const std::string &fileContent) :
        info(RequestInfo('W', 4 + fileContent.size())),
        fileDescriptor(fileDescriptor),
        fileContent(fileContent) {}
    void Deserialize(std::string val) override;
    std::string Serialize() override;
};


#endif //NFS_FILE_SERVER_WRITEREQUEST_H
