#include "CloseReply.h"
void CloseReply::Deserialize(std::string rep) {
}
std::string CloseReply::Serialize() {
    BytesConverter bc;
    std::string res = "";
    res += info.replyType;
    res += bc.IntToBytes((int)info.dataSize);
    return res;
}
