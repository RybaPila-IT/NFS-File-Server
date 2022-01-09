#ifndef NFS_FILE_SERVER_REQUESTINFO_H
#define NFS_FILE_SERVER_REQUESTINFO_H


class RequestInfo {

public:
    char requestType;
    unsigned int dataSize;
    RequestInfo(char requestType, unsigned int dataSize) : requestType(requestType), dataSize(dataSize) {}


};


#endif //NFS_FILE_SERVER_REQUESTINFO_H
