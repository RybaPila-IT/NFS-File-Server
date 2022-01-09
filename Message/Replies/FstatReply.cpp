#include "FstatReply.h"
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