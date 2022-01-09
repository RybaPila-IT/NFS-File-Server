#ifndef NFS_FILE_SERVER_LSEEKREQUEST_H
#define NFS_FILE_SERVER_LSEEKREQUEST_H
#include "Message.h"

class LseekRequest : public Message{

public:
    RequestInfo info;
    unsigned int fileDescriptor;
    int seekLength;
    LseekRequest(unsigned int fileDescriptor, int seekLength) :
        info(RequestInfo('L', 8)),
        fileDescriptor(fileDescriptor),
        seekLength(seekLength) {}
    void Deserialize(std::string val) override;
    std::string Serialize() override;
};


#endif //NFS_FILE_SERVER_LSEEKREQUEST_H
