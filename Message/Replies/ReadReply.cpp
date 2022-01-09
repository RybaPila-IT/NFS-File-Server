#include "ReadReply.h"
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
