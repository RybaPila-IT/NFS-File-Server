#include "ErrorReply.h"
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