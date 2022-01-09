#include "LseekRequest.h"
void LseekRequest::Deserialize(std::string req) {
    BytesConverter bc;
    fileDescriptor = bc.BytesToInt(req.substr(5, 4));
    seekLength = bc.BytesToInt(req.substr(9));

}
std::string LseekRequest::Serialize() {
    BytesConverter bc;
    std::string res = "";
    res += info.requestType;
    res += bc.IntToBytes((int)info.dataSize);
    res += bc.IntToBytes(fileDescriptor);
    res += bc.IntToBytes(seekLength);
    return res;
}