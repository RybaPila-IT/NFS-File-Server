#ifndef CLIENT_FILE_H
#define CLIENT_FILE_H

#include <string>

class File {

private:
    std::string    path;
    unsigned short open_mode;
    unsigned int   position;
    std::string    content;

public:
    File(unsigned short open_mode, std::string path): path(path), open_mode(open_mode), content(), position(0) {}

    std::string get_path() {
        return path;
    }

    unsigned short get_mode() {
        return open_mode;
    }

    std::string get_content() {
        return content;
    }

    void set_content(std::string& new_content) {
        content = new_content;
    }

    unsigned int get_position() {
        return position;
    }

    void set_position(unsigned int new_position) {
        position = new_position;
    }

};


#endif //CLIENT_FILE_H
