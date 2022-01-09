#include "CloseRequest.h"
void  CloseRequest::Deserialize(std::string req) {
    BytesConverter bc;
    fileDescriptor = bc.BytesToInt(req.substr(5));
}
std::string CloseRequest::Serialize() {
    BytesConverter bc;
    std::string res = "";
    res += info.requestType;
    res += bc.IntToBytes((int)info.dataSize);
    res += bc.IntToBytes(fileDescriptor);
    return res;
}
