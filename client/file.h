#ifndef CLIENT_FILE_H
#define CLIENT_FILE_H

#include <string>

class File {

private:
    std::string path;
    bool fetched;
    unsigned short open_mode;
    int position;
    std::string content;

public:
    File(unsigned short open_mode, std::string& path) : path(path), open_mode(open_mode), content(), position(0),
                                                       fetched(false) {}

    std::string get_path() {
        return path;
    }

    unsigned short get_mode() {
        return open_mode;
    }

    std::string get_content() {
        return content;
    }

    void set_content(std::string &new_content) {
        content = new_content;
        fetched = true;
    }

    int get_position() {
        return position;
    }

    void inc_position(int offset) {
        position = (offset < 0 ? std::max(0, position + offset) : std::min((int)content.size(), position + offset));
    }

    bool is_fetched() {
        return fetched;
    }

    std::string read(int bytes_amount) {
        return content.substr(position, std::min(bytes_amount, std::max(0, (int)content.size()-position-bytes_amount)));
    }

};


#endif //CLIENT_FILE_H
