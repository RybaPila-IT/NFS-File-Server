#include "UnlinkRequest.h"
void UnlinkRequest::Deserialize(std::string req) {
    filePath = req.substr(5);


}
std::string UnlinkRequest::Serialize() {
    BytesConverter bc;
    std::string res = "";
    res += info.requestType;
    res += bc.IntToBytes((int)info.dataSize);
    res += filePath;
    return res;
}

