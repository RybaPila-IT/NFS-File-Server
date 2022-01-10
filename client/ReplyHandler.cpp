#include "ReplyHandler.h"
#include <iostream>

void ReplyHandler::HandleClose(std::string message) {

    CloseReply qRep = CloseReply();
    qRep.Deserialize(message);
    std::cout << "DE: " << qRep.info.replyType << "|" << qRep.info.dataSize <<std::endl <<std::endl;
}

void ReplyHandler::HandleConnect(std::string message) {
    ConnectReply cRep = ConnectReply(1234); //TU JEST BŁĄD
    cRep.Deserialize(message);
    std::cout << "DE: " << cRep.info.replyType << "|" << cRep.info.dataSize <<"|"<< cRep.portNumber <<std::endl <<std::endl;
}

void ReplyHandler::HandleError(std::string message) {
    ErrorReply eRep = ErrorReply("");
    eRep.Deserialize(message);
    std::cout << "DE: " << eRep.info.replyType << "|" << eRep.info.dataSize << "|" << eRep.errorMsg <<std::endl <<std::endl;
}

void ReplyHandler::HandleFstat(std::string message) {
    FstatReply fRep = FstatReply("");
    fRep.Deserialize(message);
    //std::cout << "DE: " << fRep.info.replyType << "|" << fRep.info.dataSize <<"|"<< fRep.currentPosition <<std::endl <<std::endl; TU TEŻ JEST BŁĄD
}

void ReplyHandler::HandleLseek(std::string message) {
    LseekReply lRep = LseekReply(0);
    lRep.Deserialize(message);
    std::cout << "DE: " << lRep.info.replyType << "|" << lRep.info.dataSize <<"|"<< lRep.currentPosition <<std::endl <<std::endl;
}

void ReplyHandler::HandleOpen(std::string message) {
    OpenReply oRep = OpenReply(0);
    oRep.Deserialize(message);
    std::cout<< "DE: " << oRep.info.replyType << "|" << oRep.info.dataSize <<"|"<< oRep.fileDescriptor <<std::endl <<std::endl;
}

void ReplyHandler::HandleRead(std::string message) {
    ReadReply rRep = ReadReply("");
    rRep.Deserialize(message);
    std::cout<< "DE: " << rRep.info.replyType << "|" << rRep.info.dataSize <<"|"<< rRep.fileContent <<std::endl <<std::endl;
}

void ReplyHandler::HandleUnlink(std::string message) {
    UnlinkReply uRep = UnlinkReply();
    uRep.Deserialize(message);
    std::cout<< "DE: " << uRep.info.replyType << "|" << uRep.info.dataSize <<std::endl <<std::endl;
}

void ReplyHandler::HandleWrite(std::string message) {
    WriteReply wRep = WriteReply();
    wRep.Deserialize(message);
    std::cout<< "DE: " << wRep.info.replyType << "|" << wRep.info.dataSize <<std::endl <<std::endl;
}
