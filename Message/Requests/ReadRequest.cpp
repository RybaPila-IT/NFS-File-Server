#include "ReadRequest.h"
void ReadRequest::Deserialize(std::string req) {
    BytesConverter bc;
    fileDescriptor = bc.BytesToInt(req.substr(5));
}
std::string ReadRequest::Serialize() {
    BytesConverter bc;
    std::string res = "";
    res += info.requestType;
    res += bc.IntToBytes((int)info.dataSize);
    res += bc.IntToBytes(fileDescriptor);
    return res;
}

