#ifndef SERVER_LOGGER_H
#define SERVER_LOGGER_H


#include <thread>
#include <fstream>
#include <mutex>

class Logger {
private:
    std::string &file_path;

    std::ofstream logs_file;
    std::mutex logs_mutex;

    Logger(std::string &file_path);
    ~Logger();
    void unlock_logs_mutex();
    void lock_logs_mutex();
public:
    static Logger &get_instance();
    Logger(Logger const &) = delete;
    void operator=(Logger const &) = delete;
    void create_new_log(const std::string &log_info, std::thread::id thread_id);
    void show_logs_in_console();
};


#endif //SERVER_LOGGER_H
