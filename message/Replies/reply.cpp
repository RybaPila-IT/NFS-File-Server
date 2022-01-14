#include "reply.h"
#include "bytes_converter.h"

/* Error reply */
ErrorReply::ErrorReply(): reply_type('E') {}

ErrorReply::ErrorReply(const std::string &errorMsg):
        reply_type('E'),
        error_message(errorMsg) {}

void ErrorReply::Deserialize(std::string &rep) {
    error_message = rep.substr(1);
}

std::string ErrorReply::Serialize() {
    std::string res;
    res += reply_type;
    res += error_message;
    return res;
}

/* Close Reply */
CloseReply::CloseReply(): reply_type('Q') {}

void CloseReply::Deserialize(std::string &rep) {}

std::string CloseReply::Serialize() {
    std::string res;
    res += reply_type;
    return res;
}

/* Connect Reply */
ConnectReply::ConnectReply(unsigned short port_number):
        reply_type('C'),
        port_number(port_number) {}

ConnectReply::ConnectReply():
        reply_type('C'),
        port_number(0) {}

std::string ConnectReply::Serialize() {
    std::string res;
    res += reply_type;
    res += bytes_converter::IntToBytes(port_number);
    return res;
}

void ConnectReply::Deserialize(std::string &rep) {
    port_number =  bytes_converter::BytesToInt(rep.substr(1, 4));
}

/* Fstat Reply */
FstatReply::FstatReply():
        reply_type('F') {}

FstatReply::FstatReply(const std::string &fileStatus):
        reply_type('F'),
        file_status(fileStatus) {}

void FstatReply::Deserialize(std::string &rep) {
    file_status = rep.substr(1);
}

std::string FstatReply::Serialize() {
    std::string res;
    res += reply_type;
    res += file_status;
    return res;
}

/* Lseek Reply */
LseekReply::LseekReply(): reply_type('L') {}

LseekReply::LseekReply(int current_position):
    reply_type('L'),
    current_position(current_position) {}

void LseekReply::Deserialize(std::string &rep) {
    current_position = bytes_converter::BytesToInt(rep.substr(1, 4));
}

std::string LseekReply::Serialize() {
    std::string res;
    res += reply_type;
    res += bytes_converter::IntToBytes(current_position);
    return res;
}

/* Open Reply */
OpenReply::OpenReply(): reply_type('O') {}

OpenReply::OpenReply(unsigned int file_descriptor):
        reply_type('O'),
        file_descriptor(file_descriptor) {}

void OpenReply::Deserialize(std::string &rep) {
    file_descriptor = bytes_converter::BytesToInt(rep.substr(1, 4));
}

std::string OpenReply::Serialize() {
    std::string res;
    res += reply_type;
    res += bytes_converter::IntToBytes(file_descriptor);
    return res;
}

/* Read Reply */
ReadReply::ReadReply(): reply_type('R') {}

ReadReply::ReadReply(const std::string &file_content):
        reply_type('R'),
        file_content(file_content) {}

void ReadReply::Deserialize(std::string &rep) {
    file_content = rep.substr(1);
}

std::string ReadReply::Serialize() {
    std::string res;
    res += reply_type;
    res += file_content;
    return res;
}

/*Unlink Reply */
UnlinkReply::UnlinkReply(): reply_type('U') {}

void UnlinkReply::Deserialize(std::string &rep) {}

std::string UnlinkReply::Serialize() {
    std::string res;
    res += reply_type;
    return res;
}

/* Write Reply */
WriteReply::WriteReply() : reply_type('W') {};

void WriteReply::Deserialize(std::string &rep) {}

std::string WriteReply::Serialize() {
    std::string res;
    res += reply_type;
    return res;
}