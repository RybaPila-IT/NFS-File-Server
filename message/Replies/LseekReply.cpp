#include "LseekReply.h"
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