#ifndef SERVER_LOGGER_H
#define SERVER_LOGGER_H


#include <vector>
#include <thread>
#include <fstream>
#include <mutex>
#include <memory>

class Logger {
private:

    Logger();

    std::string file_path;
    std::ofstream logs_file;
    std::mutex logs_mutex;
//    std::vector<std::thread> thread_pool;
//    std::shared_ptr<Logger> logger;
//    int thread_counter;
public:
    static Logger &get_instance();
    ~Logger();

    Logger(Logger const &) = delete;
    void operator=(Logger const &) = delete;
    void create_new_log(const std::string& log_info, std::thread::id thread_id);
    void unlock_logs_mutex();
    void lock_logs_mutex();
};


#endif //SERVER_LOGGER_H
