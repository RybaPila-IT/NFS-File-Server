#ifndef MESSAGE_BYTES_CONVERTER_H
#define MESSAGE_BYTES_CONVERTER_H

#include <string>

class bytes_converter{
public:
    static std::string IntToBytes(int);
    static int BytesToInt(std::string);
   };

#endif //MESSAGE_BYTES_CONVERTER_H