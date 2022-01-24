#include <sstream>
#include "logger.h"

Logger &Logger::get_instance() {
    static Logger logger;
    return logger;
}

Logger::Logger(): file_path("logs.txt"){
    this->logs_file.open(this->file_path,std::fstream::out | std::fstream::trunc);

}

void Logger::create_new_log(const std::string& log_info, std::thread::id thread_id) {
    lock_logs_mutex();
    try {
        std::stringstream id_stream;
        id_stream << thread_id;
        std::string id_string = id_stream.str();
        this->logs_file << "Thread id: " + id_string + ". " + log_info;
    }
    catch (std::runtime_error &error) {
        throw std::runtime_error("ERROR IN: create_new_log: " + std::string(error.what()));
    }
    unlock_logs_mutex();
}

void Logger::unlock_logs_mutex() {
    logs_mutex.unlock();
}

void Logger::lock_logs_mutex() {
    logs_mutex.lock();
}

Logger::~Logger() {
    logs_file.close();
}
