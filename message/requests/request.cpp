#include <stdexcept>

#include "request.h"
#include "bytes_converter.h"

/* Close Request */
CloseRequest::CloseRequest() : request_type('Q') {}

CloseRequest::CloseRequest(std::string &path) :
        request_type('Q'),
        path(path) {}

void CloseRequest::deserialize(std::string &val) {
    path = val.substr(1);
}

std::string CloseRequest::serialize() {
    std::string res;
    res += request_type;
    res += path;
    return res;
}

std::string CloseRequest::get_path() {
    return path;
}

/* Fstat Request */
FstatRequest::FstatRequest() : request_type('F') {}

FstatRequest::FstatRequest(std::string &path) :
        request_type('F'),
        path(path) {}

void FstatRequest::deserialize(std::string &val) {
    path = val.substr(1);
}

std::string FstatRequest::serialize() {
    std::string res;
    res += request_type;
    res += path;
    return res;
}

std::string FstatRequest::get_path() {
    return path;
}

/* Open Request */
OpenRequest::OpenRequest() :
        request_type('O'), open_mode(0) {}

OpenRequest::OpenRequest(unsigned short open_mode, const std::string &file_path) :
        request_type('O'),
        open_mode(open_mode),
        path(file_path) {}

void OpenRequest::deserialize(std::string &val) {
    open_mode = BytesConverter::BytesToInt(val.substr(1, 4));
    path = val.substr(5);
}

std::string OpenRequest::serialize() {
    std::string res;
    res += request_type;
    res += BytesConverter::IntToBytes(open_mode);
    res += path;
    return res;
}

std::string OpenRequest::get_path() {
    return path;
}

unsigned short OpenRequest::get_open_mode() {
    return open_mode;
}

/* Read Request */
ReadRequest::ReadRequest() : request_type('R') {}

ReadRequest::ReadRequest(std::string &path) :
        request_type('R'),
        path(path) {}

void ReadRequest::deserialize(std::string &val) {
    path = val.substr(1);
}

std::string ReadRequest::serialize() {
    std::string res;
    res += request_type;
    res += path;
    return res;
}

std::string ReadRequest::get_path() {
    return path;
}

/* Write Request */
WriteRequest::WriteRequest() :
        request_type('W'),
        size_of_path(0) {}

WriteRequest::WriteRequest(std::string &path, const std::string &fileContent) :
        request_type('W'),
        path(path),
        size_of_path(path.size()),
        file_content(fileContent) {}

void WriteRequest::deserialize(std::string &val) {
    size_of_path = BytesConverter::BytesToInt(val.substr(1, 4));
    path = val.substr(5, size_of_path);
    file_content = val.substr(5 + size_of_path);
}

std::string WriteRequest::serialize() {
    std::string res;
    res += request_type;
    res += BytesConverter::IntToBytes(size_of_path);
    res += path;
    res += file_content;
    return res;
}

std::string WriteRequest::get_path() {
    return path;
}

std::string WriteRequest::get_file_content() {
    return file_content;
}