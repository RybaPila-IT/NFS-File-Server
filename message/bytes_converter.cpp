#include "bytes_converter.h"

std::string BytesConverter::IntToBytes(int val) {
    char bytes[4];
    bytes[3] =  val & 0x000000ff;
    bytes[2] = (val & 0x0000ff00) >> 8;
    bytes[1] = (val & 0x00ff0000) >> 16;
    bytes[0] = (val & 0xff000000) >> 24;
    return std::string(bytes, 4);
}

 int BytesConverter::BytesToInt(std::string var) {
    return (int) ((unsigned char)(var[0]) << 24 |
                  (unsigned char)(var[1]) << 16 |
                  (unsigned char)(var[2]) << 8 |
                  (unsigned char)(var[3]));
}