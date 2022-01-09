#include "RequestSorter.h"
Message* RequestSorter::DeserializeMessage(std::string ser) {
    Message* mes;
    CloseRequest q = CloseRequest(0);
    ConnectRequest c = ConnectRequest();
    FstatRequest f = FstatRequest(0);
    LseekRequest l = LseekRequest(0, 0);
    OpenRequest o = OpenRequest(0, "");
    ReadRequest r = ReadRequest(0);
    UnlinkRequest u = UnlinkRequest("");
    WriteRequest w = WriteRequest(0, "");
    switch (ser[0]) {
        case 'Q':
            q.Deserialize(ser);
            break;
        case 'C':
            c.Deserialize(ser);
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
    return mes;
}