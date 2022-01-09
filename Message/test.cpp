#include "test.h"
#include <iostream>


ErrorReply testFunct()
{
    ErrorReply errorReply = ErrorReply("TESTTEST");
    return errorReply;

}
int main()
{
    Message* x;
    Message test = testFunct();
    x = &test;
    std::cout << "FIRST " << x->Serialize() << std::endl<< std::endl ;

    CloseReply qRep;
    ConnectReply cRep = ConnectReply(1000);
    ErrorReply eRep = ErrorReply("ERRORMSGERRORMSGERRORMSG");
    FstatReply fRep = FstatReply("FileStatusFileStatusFileStatus");
    LseekReply lRep = LseekReply(100);
    OpenReply oRep = OpenReply(42);
    ReadReply rRep = ReadReply("FileContentFileContentFileContent");
    UnlinkReply uRep;
    WriteReply wRep;



    x = &qRep;
    std::cout << "PE: " << qRep.info.replyType << "|" << qRep.info.dataSize <<std::endl;
    std::cout << "SE: " << x->Serialize() << std::endl;
    qRep.Deserialize((x->Serialize()));
    std::cout << "DE: " << qRep.info.replyType << "|" << qRep.info.dataSize <<std::endl <<std::endl;

    x = &cRep;
    std::cout << "PE: " << cRep.info.replyType << "|" << cRep.info.dataSize << "|"<< cRep.portNumber <<std::endl;
    std::cout << "SE: "<< x->Serialize() << std::endl;
    cRep.Deserialize((x->Serialize()));
    std::cout << "DE: " << cRep.info.replyType << "|" << cRep.info.dataSize <<"|"<< cRep.portNumber <<std::endl <<std::endl;

    x = &eRep;
    std::cout << "PE: " << eRep.info.replyType << "|" << eRep.info.dataSize <<"|"<< eRep.errorMsg<<std::endl;
    std::cout << "SE: "<< x->Serialize() << std::endl;
    eRep.Deserialize(x->Serialize());
    std::cout << "DE: " << eRep.info.replyType << "|" << eRep.info.dataSize << "|" << eRep.errorMsg <<std::endl <<std::endl;

    x = &fRep;
    std::cout << "PE: " << fRep.info.replyType << "|" << fRep.info.dataSize << "|" << fRep.fileStatus <<std::endl;
    std::cout << "SE: "<<x->Serialize() << std::endl;
    fRep.Deserialize(x->Serialize());
    std::cout << "DE: " << fRep.info.replyType << "|" << fRep.info.dataSize <<"|"<< fRep.fileStatus <<std::endl <<std::endl;

    x = &lRep;
    std::cout << "PE: " << lRep.info.replyType << "|" << lRep.info.dataSize << "|" << lRep.currentPosition <<std::endl;
    std::cout << "SE: "<< x->Serialize() << std::endl;
    lRep.Deserialize((x->Serialize()));
    std::cout << "DE: " << lRep.info.replyType << "|" << lRep.info.dataSize <<"|"<< lRep.currentPosition <<std::endl <<std::endl;

    x = &oRep;
    std::cout << "PE: " << oRep.info.replyType << "|" << oRep.info.dataSize << "|" << oRep.fileDescriptor <<std::endl;
    std::cout << "SE: "<< x->Serialize() << std::endl;
    oRep.Deserialize((x->Serialize()));
    std::cout<< "DE: " << oRep.info.replyType << "|" << oRep.info.dataSize <<"|"<< oRep.fileDescriptor <<std::endl <<std::endl;

    x = &rRep;
    std::cout << "PE: " << rRep.info.replyType << "|" << rRep.info.dataSize << "|" << rRep.fileContent <<std::endl;
    std::cout <<"SE: " << x->Serialize() << std::endl;
    rRep.Deserialize((x->Serialize()));
    std::cout<< "DE: " << rRep.info.replyType << "|" << rRep.info.dataSize <<"|"<< rRep.fileContent <<std::endl <<std::endl;

    x = &uRep;
    std::cout<< "DE: " << uRep.info.replyType << "|" << uRep.info.dataSize <<std::endl;
    std::cout << "SE: " << x->Serialize() << std::endl;
    uRep.Deserialize((x->Serialize()));
    std::cout<< "DE: " << uRep.info.replyType << "|" << uRep.info.dataSize <<std::endl <<std::endl;

    x = &wRep;
    std::cout << "PE: "<< wRep.info.replyType << "|" <<wRep.info.dataSize << std::endl;
    std::cout << "SE: " << x->Serialize() << std::endl;
    wRep.Deserialize(x->Serialize());
    std::cout << "DE: "<< wRep.info.replyType << "|" <<wRep.info.dataSize << std::endl <<std::endl;

    CloseRequest qReq = CloseRequest(9999);
    ConnectRequest cReq;
    FstatRequest fReq = FstatRequest(6667);
    LseekRequest lReq = LseekRequest(4242, 100);
    OpenRequest oReq = OpenRequest(7, "filePathOpen");
    ReadRequest rReq = ReadRequest(1000);
    UnlinkRequest uReq = UnlinkRequest("UnlinkFilePath");
    WriteRequest wReq = WriteRequest(2222, "FileContentWrite");

    std::cout << "--------------------------------------REQUESTS-----------------------------------------------" << std::endl<<std::endl;

    x = &qReq;
    std::cout << "PE: "<< qReq.info.requestType << "|" << qReq.info.dataSize << std::endl;
    std::cout << "SE: "<<x->Serialize() <<  std::endl ;
    qReq.Deserialize(x->Serialize());
    std::cout << "DE: "<< qReq.info.requestType << "|" << qRep.info.dataSize << std::endl<<std::endl;

    x = &cReq;
    std::cout << "PE: "<< cReq.info.requestType << "|" << cReq.info.dataSize <<std::endl;
    std::cout << "SE: "<<x->Serialize() << std::endl ;
    cReq.Deserialize(x->Serialize());
    std::cout << "DE: "<< cReq.info.requestType << "|" << cReq.info.dataSize<< std::endl<<std::endl;

    x = &fReq;
    std::cout << "PE: "<< fReq.info.requestType << "|" << fReq.info.dataSize << "|" <<fReq.fileDescriptor << std::endl;
    std::cout << "SE: "<<x->Serialize() << std::endl ;
    fReq.Deserialize(x->Serialize());
    std::cout << "DE: "<< fReq.info.requestType << "|" << fReq.info.dataSize << "|" <<fReq.fileDescriptor << std::endl<<std::endl;

    x = &lReq;
    std::cout << "PE: "<< lReq.info.requestType << "|" << lReq.info.dataSize << "|"<< lReq.fileDescriptor << "|" <<lReq.seekLength<<std::endl;
    std::cout << "SE: "<<x->Serialize() << std::endl ;
    cReq.Deserialize(x->Serialize());
    std::cout << "DE: "<< lReq.info.requestType << "|" << lReq.info.dataSize <<"|"<< lReq.fileDescriptor << "|" <<lReq.seekLength<<std::endl<<std::endl;

    x = &oReq;
    std::cout << "PE: "<< oReq.info.requestType << "|" << oReq.info.dataSize <<"|"<< oReq.openMode << "|" <<oReq.filePath<<std::endl;
    std::cout << "SE: "<<x->Serialize() <<  std::endl ;
    cReq.Deserialize(x->Serialize());
    std::cout << "DE: "<< oReq.info.requestType << "|" << oReq.info.dataSize << "|" <<oReq.openMode << "|" <<oReq.filePath<<std::endl<<std::endl;

    x = &rReq;
    std::cout << "PE: "<< rReq.info.requestType << "|" << rReq.info.dataSize << "|"<< rReq.fileDescriptor <<std::endl;
    std::cout << "SE: "<<x->Serialize() << std::endl ;
    cReq.Deserialize(x->Serialize());
    std::cout << "DE: "<< rReq.info.requestType << "|" << rReq.info.dataSize <<"|"<< rReq.fileDescriptor <<std::endl<<std::endl;

    x = &uReq;
    std::cout << "PE: "<< uReq.info.requestType << "|" << uReq.info.dataSize << "|"<< uReq.filePath <<std::endl;
    std::cout << "SE: "<<x->Serialize() << std::endl ;
    cReq.Deserialize(x->Serialize());
    std::cout << "DE: "<< uReq.info.requestType << "|" << uReq.info.dataSize << "|"<< uReq.filePath <<std::endl<<std::endl;

    x = &wReq;
    std::cout << "PE: "<< wReq.info.requestType << "|" << wReq.info.dataSize << "|"<< wReq.fileDescriptor<<"|"<< wReq.fileContent <<std::endl;
    std::cout << "SE: "<<x->Serialize() << std::endl ;
    cReq.Deserialize(x->Serialize());
    std::cout << "PE: "<< wReq.info.requestType << "|" << wReq.info.dataSize << "|"<< wReq.fileDescriptor<<"|"<< wReq.fileContent <<std::endl<<std::endl;

}