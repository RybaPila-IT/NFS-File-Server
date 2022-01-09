#include "ConnectRequest.h"
void ConnectRequest::Deserialize(std::string req) {

}
std::string ConnectRequest::Serialize() {
    BytesConverter bc;
    std::string res = "";
    res += info.requestType;
    res += bc.IntToBytes((int)info.dataSize);
    return res;
}
