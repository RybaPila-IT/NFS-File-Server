#ifndef SERVER_ACCESS_MANAGER_H
#define SERVER_ACCESS_MANAGER_H

#include <atomic>
#include <string>
#include <unordered_map>

class FileGuard {
    std::atomic<bool> is_open_by_writer_lock;
    std::atomic<bool> is_operated_on_lock;

public:
    bool is_open_by_writer();

    void set_lock(bool);

    bool is_operated_on();

    void set_operated(bool);

    FileGuard();

    FileGuard(FileGuard &&file);
};

class AccessManager {
private:
    AccessManager() = default;

    std::unordered_map<std::string, FileGuard> files;

    bool is_file_existing_in_files(std::string &path);

    void add_file_if_it_does_not_exist(std::string &path);

    bool is_file_operated_on(std::string &path);

public:

    static AccessManager &get_instance();

    AccessManager(AccessManager const &) = delete;

    void operator=(AccessManager const &) = delete;

    bool is_file_blocked(std::string &path);

    void block_file_for_writer(std::string &path);

    void remove_block(std::string &path);

    void wait_to_operate(std::string &path);

    void set_operated_on(std::string &path, bool);

};

#endif //SERVER_ACCESS_MANAGER_H
