#include "ConnectReply.h"
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