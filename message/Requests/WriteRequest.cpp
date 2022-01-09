#include "WriteRequest.h"
void WriteRequest::Deserialize(std::string req) {
    BytesConverter bc;
    fileDescriptor = bc.BytesToInt(req.substr(5, 4));
    fileContent =  req.substr(9);

}
std::string WriteRequest::Serialize() {
    BytesConverter bc;
    std::string res = "";
    res += info.requestType;
    res += bc.IntToBytes((int)info.dataSize);
    res += bc.IntToBytes(fileDescriptor);
    res += fileContent;
    return res;
}

