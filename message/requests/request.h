#ifndef NFS_FILE_SERVER_REQUEST_H
#define NFS_FILE_SERVER_REQUEST_H

class CloseRequest {
    const char request_type;
    std::string path;
public:
    CloseRequest();
    CloseRequest(std::string &path);
    void deserialize(std::string& val);
    std::string serialize();
    std::string get_path();
};

class FstatRequest {
    const char request_type;
    std::string path;
public:
    FstatRequest();
    FstatRequest(std::string &path);
    void deserialize(std::string &val);
    std::string serialize();
    std::string get_path();
};

class OpenRequest {
    const char request_type;
    unsigned short open_mode;
    std::string path;
public:
    OpenRequest();
    OpenRequest(unsigned short openMode, const std::string &file_path);
    void deserialize(std::string &val);
    std::string serialize();
    std::string get_path();
    unsigned short get_open_mode();
};

class ReadRequest {
    const char request_type;
    std::string path;
public:
    ReadRequest();
    ReadRequest(std::string &path);
    void deserialize(std::string &val);
    std::string serialize();
    std::string get_path();
};

class UnlinkRequest {
    const char request_type;
    std::string path;
public:
    UnlinkRequest();
    UnlinkRequest(std::string &path);
    void deserialize(std::string &val);
    std::string serialize();
    std::string get_path();
};

class WriteRequest {
    const char request_type;
    std::string path;
    unsigned int size_of_path;
    std::string file_content;
public:
    WriteRequest();
    WriteRequest(std::string &path, const std::string &file_content);
    void deserialize(std::string &val);
    std::string serialize();
    std::string get_path();
    std::string get_file_content();
};

#endif //NFS_FILE_SERVER_REQUEST_H