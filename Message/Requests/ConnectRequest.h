#ifndef NFS_FILE_SERVER_CONNECTREQUEST_H
#define NFS_FILE_SERVER_CONNECTREQUEST_H
#include "../Message.h"

class ConnectRequest : public Message{

public:
    RequestInfo info;
    ConnectRequest(): info(RequestInfo('C', 0)){};
    void Deserialize(std::string val) override;
    std::string Serialize() override;
};


#endif //NFS_FILE_SERVER_CONNECTREQUEST_H
