#include "Message.h"
//OBECNIE NIEUŻYWANE
//W CELU UŻYCIA, ODKOMENTOWAĆ ZAWARTOŚĆ Message.h oraz Message.cpp
//SZCZEGÓŁY W Message.h
/*
//REPLIES----------------------------------------------------------
void CloseReply::Deserialize(std::string rep) {}

std::string CloseReply::Serialize() {
    BytesConverter bc;
    std::string res = "";
    res += info.replyType;
    res += bc.IntToBytes((int)info.dataSize);
    return res;
}

void ConnectReply::Deserialize(std::string rep) {
    BytesConverter bc;
    portNumber =  bc.BytesToInt(rep.substr(5));
}

std::string ConnectReply::Serialize() {
    BytesConverter bc;
    std::string res = "";
    res += info.replyType;
    res += bc.IntToBytes((int)info.dataSize);
    res += bc.IntToBytes(portNumber);
    return res;
}

void ErrorReply::Deserialize(std::string rep) {
    errorMsg = rep.substr(5);
}

std::string ErrorReply::Serialize() {
    BytesConverter bc;
    std::string res = "";
    res += info.replyType;
    res += bc.IntToBytes((int)info.dataSize);
    res += errorMsg;
    return res;
}

void FstatReply::Deserialize(std::string rep) {
    fileStatus = rep.substr(5);
}

std::string FstatReply::Serialize() {
    BytesConverter bc;
    std::string res = "";
    res += info.replyType;
    res += bc.IntToBytes((int)info.dataSize);
    res += fileStatus;
    return res;
}

void LseekReply::Deserialize(std::string rep) {
    BytesConverter bc;
    currentPosition = bc.BytesToInt(rep.substr(5));
}

std::string LseekReply::Serialize() {
    BytesConverter bc;
    std::string res = "";
    res += info.replyType;
    res += bc.IntToBytes((int)info.dataSize);
    res += bc.IntToBytes(currentPosition);
    return res;
}

void OpenReply::Deserialize(std::string rep) {
    BytesConverter bc;
    fileDescriptor = bc.BytesToInt(rep.substr(5));
}

std::string OpenReply::Serialize() {
    BytesConverter bc;
    std::string res = "";
    res += info.replyType;
    res += bc.IntToBytes((int)info.dataSize);
    res += bc.IntToBytes(fileDescriptor);
    return res;
}

void ReadReply::Deserialize(std::string rep) {
    fileContent = rep.substr(5);
}

std::string ReadReply::Serialize() {
    BytesConverter bc;
    std::string res = "";
    res += info.replyType;
    res += bc.IntToBytes((int)info.dataSize);
    res += fileContent;
    return res;
}

void UnlinkReply::Deserialize(std::string rep) {}

std::string UnlinkReply::Serialize() {
    BytesConverter bc;
    std::string res = "";
    res += info.replyType;
    res += bc.IntToBytes((int)info.dataSize);
    return res;
}

void WriteReply::Deserialize(std::string rep) {}

std::string WriteReply::Serialize() {
    BytesConverter bc;
    std::string res = "";
    res += info.replyType;
    res += bc.IntToBytes((int)info.dataSize);
    return res;
}

//REQUESTS----------------------------------------------------------------------------
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

 */