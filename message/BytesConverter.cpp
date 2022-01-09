#include "BytesConverter.h"

std::string BytesConverter::IntToBytes(int val) {
    std::string res = "";
    unsigned char bytes[4];
    bytes[0] = (val >> 24) & 0xFF;
    //std::cout<< "B1: "<< ((val >> 24) & 0xFF)  << std::endl;
    bytes[1] = (val >> 16) & 0xFF;
    //std::cout<< "B2: "<< ((val >> 16) & 0xFF) << std::endl;
    bytes[2] = (val >> 8) & 0xFF;
    //std::cout<< "B3: "<< ((val >> 8) & 0xFF) << std::endl;
    bytes[3] = val & 0xFF;
    //std::cout<< "B4: "<< (val & 0xFF) << std::endl;

    res += bytes[0];
    res += bytes[1];
    res += bytes[2];
    res += bytes[3];

    return res;
}

 int BytesConverter::BytesToInt(std::string var) {
    unsigned char val[4];
    val[0] = var[0];
    val[1] = var[1];
    val[2] = var[2];
    val[3] = var[3];

    int i = val[0];
    //std::cout<< "i: "<< i << std::endl;
    i = i << 8;
    //std::cout<< "im: "<< i << std::endl;
    i += val[1];
    //std::cout<< "i: "<< i << std::endl;
    i  = i << 8;
   // std::cout<< "im: "<< i << std::endl;
    i += val[2];
    //std::cout<< "i: "<< i << std::endl;
    i  = i << 8;
   // std::cout<< "im: "<< i << std::endl;
    i += val[3];
    //std::cout<< "i: "<< i << std::endl;
    return i;


}