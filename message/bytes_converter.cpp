#include "bytes_converter.h"

std::string bytes_converter::IntToBytes(int val) {
    std::string res;
    unsigned char bytes[4];
    bytes[0] = (val >> 24) & 0xFF;
    bytes[1] = (val >> 16) & 0xFF;
    bytes[2] = (val >> 8) & 0xFF;
    bytes[3] = val & 0xFF;

    res += bytes[0];
    res += bytes[1];
    res += bytes[2];
    res += bytes[3];

    return res;
}

 int bytes_converter::BytesToInt(std::string var) {
    unsigned char val[4];
    val[0] = var[0];
    val[1] = var[1];
    val[2] = var[2];
    val[3] = var[3];

    int i = val[0];
    i = i << 8;
    i += val[1];
    i  = i << 8;
    i += val[2];
    i  = i << 8;
    i += val[3];

    return i;
}