#ifndef NFS_FILE_SERVER_MESSAGE_H
#define NFS_FILE_SERVER_MESSAGE_H
#include "ReplyInfo.h"
#include "RequestInfo.h"
#include "BytesConverter.h"

class Message {
public:
    virtual std::string Serialize()=0;
    virtual void Deserialize(std::string)=0;

};


#endif //NFS_FILE_SERVER_MESSAGE_H
