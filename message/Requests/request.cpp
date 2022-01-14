#include <stdexcept>

#include "request.h"
#include "bytes_converter.h"

#define DUMMY_FILE_DESCRIPTOR 1000

/* Close Request */
CloseRequest::CloseRequest():
    info(request_info('Q', 5)),
    fileDescriptor(DUMMY_FILE_DESCRIPTOR) {}

CloseRequest::CloseRequest(unsigned int fileDescriptor):
    info(request_info('Q', 5)),
    fileDescriptor(fileDescriptor) {}

void  CloseRequest::Deserialize(std::string& req) {
    fileDescriptor = bytes_converter::BytesToInt(req.substr(1, 4));
}

std::string CloseRequest::Serialize() {
    std::string res;
    res += bytes_converter::IntToBytes((int)info.dataSize);
    res += info.requestType;
    res += bytes_converter::IntToBytes(fileDescriptor);
    return res;
}

/* Connect Request */
ConnectRequest::ConnectRequest():
    info(request_info('C', 1)){}

void ConnectRequest::Deserialize(std::string &req) {
    throw std::runtime_error("Request - ConnectRequest deserialize not implemented");
}

std::string ConnectRequest::Serialize() {
    std::string res;
    res += bytes_converter::IntToBytes((int)info.dataSize);
    res += info.requestType;
    return res;
}

/* Fstat Request */
FstatRequest::FstatRequest():
    info(request_info('F', 5)),
    fileDescriptor(DUMMY_FILE_DESCRIPTOR) {}

FstatRequest::FstatRequest(unsigned int fileDescriptor):
        info(request_info('F', 5)),
        fileDescriptor(fileDescriptor) {}

void FstatRequest::Deserialize(std::string &req) {
    fileDescriptor = bytes_converter::BytesToInt(req.substr(1, 4));
}

std::string FstatRequest::Serialize() {
    std::string res;
    res += bytes_converter::IntToBytes((int)info.dataSize);
    res += info.requestType;
    res += bytes_converter::IntToBytes(fileDescriptor);
    return res;
}

/* Lseek Request */
LseekRequest::LseekRequest():
    info(request_info('L', 9)),
    fileDescriptor(DUMMY_FILE_DESCRIPTOR),
    seekLength(-1) {}

LseekRequest::LseekRequest(unsigned int fileDescriptor, int seekLength):
    info(request_info('L', 9)),
    fileDescriptor(fileDescriptor),
    seekLength(seekLength) {}

void LseekRequest::Deserialize(std::string& req) {
    fileDescriptor = bytes_converter::BytesToInt(req.substr(1, 4));
    seekLength = bytes_converter::BytesToInt(req.substr(5, 4));
}

std::string LseekRequest::Serialize() {
    std::string res;
    res += bytes_converter::IntToBytes((int)info.dataSize);
    res += info.requestType;
    res += bytes_converter::IntToBytes(fileDescriptor);
    res += bytes_converter::IntToBytes(seekLength);
    return res;
}

/* Open Request */
OpenRequest::OpenRequest():
    info(request_info('O', 5)),
    openMode(0) {}

OpenRequest::OpenRequest(unsigned short openMode, const std::string &filePath):
        info(request_info('O', 5 + filePath.size())),
        openMode(openMode),
        filePath(filePath) {}

void OpenRequest::Deserialize(std::string &req) {
    openMode = bytes_converter::BytesToInt(req.substr(1, 4));
    filePath = req.substr(5);
}

std::string OpenRequest::Serialize() {
    std::string res;
    res += bytes_converter::IntToBytes((int)info.dataSize);
    res += info.requestType;
    res += bytes_converter::IntToBytes(openMode);
    res += filePath;
    return res;
}

/* Read Request */
ReadRequest::ReadRequest():
        info(request_info('R', 5)),
        fileDescriptor(DUMMY_FILE_DESCRIPTOR) {}

ReadRequest::ReadRequest(unsigned int fileDescriptor) :
        info(request_info('R', 5)),
        fileDescriptor(fileDescriptor) {}

void ReadRequest::Deserialize(std::string &req) {
    fileDescriptor = bytes_converter::BytesToInt(req.substr(1, 4));
}

std::string ReadRequest::Serialize() {
    std::string res;
    res += bytes_converter::IntToBytes((int)info.dataSize);
    res += info.requestType;
    res += bytes_converter::IntToBytes(fileDescriptor);
    return res;
}

/*Unlink Request */
UnlinkRequest::UnlinkRequest() :
        info(request_info('U', 1)) {}

UnlinkRequest::UnlinkRequest(const std::string &filePath) :
        info(request_info('U', 1 + filePath.size() )),
        filePath(filePath) {}

void UnlinkRequest::Deserialize(std::string &req) {
    filePath = req.substr(1);
}

std::string UnlinkRequest::Serialize() {
    std::string res;
    res += bytes_converter::IntToBytes((int)info.dataSize);
    res += info.requestType;
    res += filePath;
    return res;
}

/* Write Request */
WriteRequest::WriteRequest():
        info(request_info('W', 5)),
        fileDescriptor(DUMMY_FILE_DESCRIPTOR) {}

WriteRequest::WriteRequest(unsigned int fileDescriptor, const std::string &fileContent) :
        info(request_info('W', 5 + fileContent.size())),
        fileDescriptor(fileDescriptor),
        fileContent(fileContent) {}

void WriteRequest::Deserialize(std::string &req) {
    fileDescriptor = bytes_converter::BytesToInt(req.substr(1, 4));
    fileContent =  req.substr(5);
}

std::string WriteRequest::Serialize() {
    std::string res;
    res += bytes_converter::IntToBytes((int)info.dataSize);
    res += info.requestType;
    res += bytes_converter::IntToBytes(fileDescriptor);
    res += fileContent;
    return res;
}