#include "OpenRequest.h"
void OpenRequest::Deserialize(std::string req) {
    BytesConverter bc;
    openMode = bc.BytesToInt(req.substr(5, 4));
    filePath = req.substr(9);

}
std::string OpenRequest::Serialize() {
    BytesConverter bc;
    std::string res = "";
    res += info.requestType;
    res += bc.IntToBytes((int)info.dataSize);
    res += bc.IntToBytes(openMode);
    res += filePath;
    return res;
}

