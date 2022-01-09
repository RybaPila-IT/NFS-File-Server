#include "UnlinkReply.h"
void UnlinkReply::Deserialize(std::string rep) {

}
std::string UnlinkReply::Serialize() {
    BytesConverter bc;
    std::string res = "";
    res += info.replyType;
    res += bc.IntToBytes((int)info.dataSize);
    return res;
}