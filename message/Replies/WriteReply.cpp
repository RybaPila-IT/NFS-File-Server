#include "WriteReply.h"
void WriteReply::Deserialize(std::string rep) {

}
std::string WriteReply::Serialize() {
    BytesConverter bc;
    std::string res = "";
    res += info.replyType;
    res += bc.IntToBytes((int)info.dataSize);
    return res;
}

