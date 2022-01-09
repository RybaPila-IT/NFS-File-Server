#include "RequestHandler.h"
#include <iostream>

void RequestHandler::HandleClose(std::string message) {
    CloseRequest qReq = CloseRequest(0);
    qReq.Deserialize(message);
    std::cout << "DE: "<< qReq.info.requestType << "|" << qReq.info.dataSize << std::endl<<std::endl;
}

void RequestHandler::HandleConnect(std::string message) {
    ConnectRequest cReq = ConnectRequest();
    cReq.Deserialize(message);
    std::cout << "DE: "<< cReq.info.requestType << "|" << cReq.info.dataSize<< std::endl<<std::endl;
}

void RequestHandler::HandleFstat(std::string message) {
    FstatRequest fReq = FstatRequest(0);
    fReq.Deserialize(message);
    std::cout << "DE: "<< fReq.info.requestType << "|" << fReq.info.dataSize << "|" <<fReq.fileDescriptor << std::endl<<std::endl;
}

void RequestHandler::HandleLseek(std::string message) {
    LseekRequest lReq = LseekRequest(0, 0);
    lReq.Deserialize(message);
    std::cout << "DE: "<< lReq.info.requestType << "|" << lReq.info.dataSize <<"|"<< lReq.fileDescriptor << "|" <<lReq.seekLength<<std::endl<<std::endl;
}

void RequestHandler::HandleOpen(std::string message) {
    OpenRequest oReq = OpenRequest(0,"");
    oReq.Deserialize(message);
    std::cout << "DE: "<< oReq.info.requestType << "|" << oReq.info.dataSize << "|" <<oReq.openMode << "|" <<oReq.filePath<<std::endl<<std::endl;
}

void RequestHandler::HandleRead(std::string message) {
    ReadRequest rReq = ReadRequest(0);
    rReq.Deserialize(message);
    std::cout << "DE: "<< rReq.info.requestType << "|" << rReq.info.dataSize <<"|"<< rReq.fileDescriptor <<std::endl<<std::endl;
}

void RequestHandler::HandleUnlink(std::string message) {
    UnlinkRequest uReq = UnlinkRequest("");
    uReq.Deserialize(message);
    std::cout << "DE: "<< uReq.info.requestType << "|" << uReq.info.dataSize << "|"<< uReq.filePath <<std::endl<<std::endl;
}

void RequestHandler::HandleWrite(std::string message) {
    WriteRequest wReq = WriteRequest(0, "");
    wReq.Deserialize(message);
    std::cout << "PE: "<< wReq.info.requestType << "|" << wReq.info.dataSize << "|"<< wReq.fileDescriptor<<"|"<< wReq.fileContent <<std::endl<<std::endl;
}