#ifndef NFS_FILE_SERVER_REPLYINFO_H
#define NFS_FILE_SERVER_REPLYINFO_H


class ReplyInfo {
public:
    char replyType;
    unsigned int dataSize;
    ReplyInfo(char replyType, unsigned int dataSize) : replyType(replyType), dataSize(dataSize) {}

};


#endif //NFS_FILE_SERVER_REPLYINFO_H
