#ifndef MESSAGE_REPLYSORTER_H
#define MESSAGE_REPLYSORTER_H
#include "CloseReply.h"
#include "ConnectReply.h"
#include "ErrorReply.h"
#include "FstatReply.h"
#include "LseekReply.h"
#include "OpenReply.h"
#include "ReadReply.h"
#include "UnlinkReply.h"
#include "WriteReply.h"

class ReplySorter {
public:
    void DeserializeMessage(std::string);
};
#endif //MESSAGE_REPLYSORTER_H
