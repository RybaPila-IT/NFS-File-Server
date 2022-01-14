#ifndef MESSAGE_BYTES_CONVERTER_H
#define MESSAGE_BYTES_CONVERTER_H

#include <string>

class BytesConverter{
public:
    static std::string IntToBytes(int);
    static int BytesToInt(std::string);
   };

#endif //MESSAGE_BYTES_CONVERTER_H