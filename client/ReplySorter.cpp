#include "ReplySorter.h"

void ReplySorter::DeserializeMessage(std::string ser) {
    ReplyHandler rp;

    switch (ser[0]) {
        case 'Q':
            rp.HandleClose(ser);
            break;
        case 'C':
            rp.HandleConnect(ser);
            break;
        case 'E':
            rp.HandleError(ser);
            break;
        case 'F':
            rp.HandleFstat(ser);
            break;
        case 'L':
            rp.HandleLseek(ser);
            break;
        case 'O':
            rp.HandleOpen(ser);
            break;
        case 'R':
            rp.HandleRead(ser);
            break;
        case 'U':
            rp.HandleUnlink(ser);
            break;
        case 'W':
            rp.HandleWrite(ser);
            break;

    }
}