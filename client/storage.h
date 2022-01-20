#ifndef CLIENT_STORAGE_H
#define CLIENT_STORAGE_H

#include <unordered_map>

#include "file.h"


class Storage {

private:
    static int new_file_descriptor;

    struct file_meta {
        int  desc;
        bool fetched;
    };

    // Shorter version of file_name_to_meta.
    using fn_to_meta = std::unordered_map<std::string, file_meta>;
    // Shorter version of descriptor_to_file.
    using desc_to_f = std::unordered_map<int, File>;

    fn_to_meta files_meta;
    desc_to_f  opened_files;

public:

    int  get_file_descriptor(std::string& file_path);
    int  add_file(std::string& file_path, File& file);
    void erase_file(int desc);
    std::string desc_to_file_path(int desc);
    void set_file_content(int desc, std::string& content);

    File obtain_file(int desc);

};

#endif //CLIENT_STORAGE_H
