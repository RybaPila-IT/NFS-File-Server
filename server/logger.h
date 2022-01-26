#ifndef SERVER_LOGGER_H
#define SERVER_LOGGER_H

#include <thread>
#include <fstream>
#include <mutex>

class Logger {
private:
    static const std::string file_path;

    std::ofstream logs_file;
    std::mutex logs_mutex;

    Logger();
    Logger(Logger const &) = delete;
    ~Logger();

    void unlock_logs_mutex();
    void lock_logs_mutex();

public:
    static Logger &get_instance();

    void create_new_log(const std::string &log_info, std::thread::id thread_id);
};

#endif //SERVER_LOGGER_H
