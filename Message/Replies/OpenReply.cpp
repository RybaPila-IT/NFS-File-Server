#include "OpenReply.h"
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