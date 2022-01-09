#include "RequestSorter.h"
void RequestSorter::DeserializeMessage(std::string ser) {
    RequestHandler rq;

    switch (ser[0]) {
        case 'Q':
            rq.HandleClose(ser);
            break;
        case 'C':
            rq.HandleConnect(ser);
            break;
        case 'F':
            rq.HandleFstat(ser);
            break;
        case 'L':
            rq.HandleLseek(ser);
            break;
        case 'O':
            rq.HandleOpen(ser);
            break;
        case 'R':
            rq.HandleRead(ser);
            break;
        case 'U':
            rq.HandleUnlink(ser);
            break;
        case 'W':
            rq.HandleWrite(ser);
            break;

    }
}