#ifndef MESSAGE_REQUESTSORTER_H
#define MESSAGE_REQUESTSORTER_H
#include "CloseRequest.h"
#include "ConnectRequest.h"
#include "FstatRequest.h"
#include "LseekRequest.h"
#include "OpenRequest.h"
#include "ReadRequest.h"
#include "UnlinkRequest.h"
#include "WriteRequest.h"

class RequestSorter {
public:
    Message* DeserializeMessage(std::string);
};


#endif //MESSAGE_REQUESTSORTER_H
