#include "Reply.h"
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