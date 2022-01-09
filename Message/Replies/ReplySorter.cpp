#include "ReplySorter.h"
void ReplySorter::DeserializeMessage(std::string ser) {
    Message* mes;
    CloseReply q = CloseReply();
    ConnectReply c = ConnectReply(0);
    ErrorReply e = ErrorReply("");
    FstatReply f = FstatReply("");
    LseekReply l = LseekReply(0);
    OpenReply o = OpenReply(0);
    ReadReply r = ReadReply("");
    UnlinkReply u = UnlinkReply();
    WriteReply w = WriteReply();

    switch (ser[0]) {
        case 'Q':
            q.Deserialize(ser);
            break;
        case 'C':
            c.Deserialize(ser);
            break;
        case 'E':
            e.Deserialize(ser);
            break;
        case 'F':
            f.Deserialize(ser);
            break;
        case 'L':
            l.Deserialize(ser);
            break;
        case 'O':
            o.Deserialize(ser);
            break;
        case 'R':
            r.Deserialize(ser);
            break;
        case 'U':
            u.Deserialize(ser);
            break;
        case 'W':
            w.Deserialize(ser);
            break;

    }
}