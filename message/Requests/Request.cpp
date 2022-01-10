#include "Request.h"
void  CloseRequest::Deserialize(std::string req) {
    BytesConverter bc;
    fileDescriptor = bc.BytesToInt(req.substr(5));
}

std::string CloseRequest::Serialize() {
    BytesConverter bc;
    std::string res = "";
    res += info.requestType;
    res += bc.IntToBytes((int)info.dataSize);
    res += bc.IntToBytes(fileDescriptor);
    return res;
}

void ConnectRequest::Deserialize(std::string req) {}

std::string ConnectRequest::Serialize() {
    BytesConverter bc;
    std::string res = "";
    res += info.requestType;
    res += bc.IntToBytes((int)info.dataSize);
    return res;
}

void FstatRequest::Deserialize(std::string req) {
    BytesConverter bc;
    fileDescriptor = bc.BytesToInt(req.substr(5));
}

std::string FstatRequest::Serialize() {
    BytesConverter bc;
    std::string res = "";
    res += info.requestType;
    res += bc.IntToBytes((int)info.dataSize);
    res += bc.IntToBytes(fileDescriptor);
    return res;
}

void LseekRequest::Deserialize(std::string req) {
    BytesConverter bc;
    fileDescriptor = bc.BytesToInt(req.substr(5, 4));
    seekLength = bc.BytesToInt(req.substr(9));
}

std::string LseekRequest::Serialize() {
    BytesConverter bc;
    std::string res = "";
    res += info.requestType;
    res += bc.IntToBytes((int)info.dataSize);
    res += bc.IntToBytes(fileDescriptor);
    res += bc.IntToBytes(seekLength);
    return res;
}

void OpenRequest::Deserialize(std::string req) {
    BytesConverter bc;
    openMode = bc.BytesToInt(req.substr(5, 4));
    filePath = req.substr(9);
}

std::string OpenRequest::Serialize() {
    BytesConverter bc;
    std::string res = "";
    res += info.requestType;
    res += bc.IntToBytes((int)info.dataSize);
    res += bc.IntToBytes(openMode);
    res += filePath;
    return res;
}

void ReadRequest::Deserialize(std::string req) {
    BytesConverter bc;
    fileDescriptor = bc.BytesToInt(req.substr(5));
}

std::string ReadRequest::Serialize() {
    BytesConverter bc;
    std::string res = "";
    res += info.requestType;
    res += bc.IntToBytes((int)info.dataSize);
    res += bc.IntToBytes(fileDescriptor);
    return res;
}

void UnlinkRequest::Deserialize(std::string req) {
    filePath = req.substr(5);
}

std::string UnlinkRequest::Serialize() {
    BytesConverter bc;
    std::string res = "";
    res += info.requestType;
    res += bc.IntToBytes((int)info.dataSize);
    res += filePath;
    return res;
}

void WriteRequest::Deserialize(std::string req) {
    BytesConverter bc;
    fileDescriptor = bc.BytesToInt(req.substr(5, 4));
    fileContent =  req.substr(9);
}

std::string WriteRequest::Serialize() {
    BytesConverter bc;
    std::string res = "";
    res += info.requestType;
    res += bc.IntToBytes((int)info.dataSize);
    res += bc.IntToBytes(fileDescriptor);
    res += fileContent;
    return res;
}