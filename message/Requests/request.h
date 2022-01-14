#ifndef NFS_FILE_SERVER_REQUEST_H
#define NFS_FILE_SERVER_REQUEST_H

class request_info {
public:
    char requestType;
    unsigned int dataSize;
    request_info(char requestType, unsigned int dataSize) : requestType(requestType), dataSize(dataSize) {}
};

class CloseRequest {
    request_info info;
    unsigned int fileDescriptor;
public:
    CloseRequest();
    CloseRequest(unsigned int fileDescriptor);
    void Deserialize(std::string& val);
    std::string Serialize();
};

class ConnectRequest {
    request_info info;
public:
    ConnectRequest();
    void Deserialize(std::string &val);
    std::string Serialize();
};

class FstatRequest {
    request_info info;
    unsigned int fileDescriptor;
public:
    FstatRequest();
    FstatRequest(unsigned int fileDescriptor);
    void Deserialize(std::string &val);
    std::string Serialize();
};

class LseekRequest {
    request_info info;
    unsigned int fileDescriptor;
    int seekLength;
public:
    LseekRequest();
    LseekRequest(unsigned int fileDescriptor, int seekLength);
    void Deserialize(std::string &val);
    std::string Serialize();
};

class OpenRequest {
    request_info info;
    unsigned short openMode;
    std::string filePath;
public:
    OpenRequest();
    OpenRequest(unsigned short openMode, const std::string &filePath);
    void Deserialize(std::string &val);
    std::string Serialize();
};

class ReadRequest {
    request_info info;
    unsigned int fileDescriptor;
public:
    ReadRequest();
    ReadRequest(unsigned int fileDescriptor);
    void Deserialize(std::string &val);
    std::string Serialize();
};

class UnlinkRequest {
    request_info info;
    std::string filePath;
public:
    UnlinkRequest();
    UnlinkRequest(const std::string &filePath);
    void Deserialize(std::string &val);
    std::string Serialize();
};

class WriteRequest {
    request_info info;
    unsigned int fileDescriptor;
    std::string fileContent;
public:
    WriteRequest();
    WriteRequest(unsigned int fileDescriptor, const std::string &fileContent);
    void Deserialize(std::string &val);
    std::string Serialize();
};

#endif //NFS_FILE_SERVER_REQUEST_H
