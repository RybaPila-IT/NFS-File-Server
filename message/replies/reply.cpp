#include "reply.h"

/* Error reply */
ErrorReply::ErrorReply(): reply_type('E') {}

ErrorReply::ErrorReply(const std::string &errorMsg):
        reply_type('E'),
        error_message(errorMsg) {}

void ErrorReply::deserialize(std::string &val) {
    error_message = val.substr(1);
}

std::string ErrorReply::serialize() {
    std::string res;
    res += reply_type;
    res += error_message;
    return res;
}

std::string ErrorReply::get_error_message() {
    return error_message;
}

/* Close Reply */
CloseReply::CloseReply(): reply_type('Q') {}

void CloseReply::deserialize(std::string &val) {}

std::string CloseReply::serialize() {
    std::string res;
    res += reply_type;
    return res;
}

/* Fstat Reply */
FstatReply::FstatReply():
        reply_type('F') {}

FstatReply::FstatReply(const std::string &fileStatus):
        reply_type('F'),
        file_status(fileStatus) {}

void FstatReply::deserialize(std::string &val) {
    file_status = val.substr(1);
}

std::string FstatReply::serialize() {
    std::string res;
    res += reply_type;
    res += file_status;
    return res;
}

std::string FstatReply::get_file_status() {
    return file_status;
}

/* Open Reply */
OpenReply::OpenReply(): reply_type('O') {}

void OpenReply::deserialize(std::string &val) {
    //TODO
}

std::string OpenReply::serialize() {
    std::string res;
    res += reply_type;
    //TODO
    //res += BytesConverter::IntToBytes(file_descriptor);
    return res;
}

/* Read Reply */
ReadReply::ReadReply(): reply_type('R') {}

ReadReply::ReadReply(const std::string &file_content):
        reply_type('R'),
        file_content(file_content) {}

void ReadReply::deserialize(std::string &val) {
    file_content = val.substr(1);
}

std::string ReadReply::serialize() {
    std::string res;
    res += reply_type;
    res += file_content;
    return res;
}

std::string ReadReply::get_file_content() {
    return file_content;
}

/*Unlink Reply */
UnlinkReply::UnlinkReply(): reply_type('U') {}

void UnlinkReply::deserialize(std::string &val) {}

std::string UnlinkReply::serialize() {
    std::string res;
    res += reply_type;
    return res;
}

/* Write Reply */
WriteReply::WriteReply() : reply_type('W') {}

void WriteReply::deserialize(std::string &val) {}

std::string WriteReply::serialize() {
    std::string res;
    res += reply_type;
    return res;
}