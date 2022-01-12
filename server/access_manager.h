#ifndef SERVER_ACCESS_MANAGER_H
#define SERVER_ACCESS_MANAGER_H

#include <atomic>
#include <string>
#include <vector>

class File_Guard {
public:
    std::atomic<bool> is_open_by_writer;
    std::string path;
    File_Guard(std::string &path);
    File_Guard(File_Guard &&file);
};

class access_manager {
private:
    access_manager()= default;
    std::vector<File_Guard> files;

    bool is_file_existing_in_files(std::string &path);
    void add_file_if_it_does_not_exist(std::string &path);

public:
    static access_manager& get_instance();
    access_manager(access_manager const&) = delete;
    void operator=(access_manager const&) = delete;

    bool is_file_blocked(std::string &path);
    void block_file_for_writer(std::string &path);
    void remove_block(std::string &path);
};

#endif //SERVER_ACCESS_MANAGER_H
