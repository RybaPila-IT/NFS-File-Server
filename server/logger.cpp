#include <sstream>
#include <iostream>

#include "logger.h"

std::string const Logger::file_path = "logs.txt";

Logger &Logger::get_instance() {
    static Logger logger;
    return logger;
}

Logger::Logger(){
    try {
        logs_file.open(file_path, std::fstream::out | std::fstream::trunc);
    } catch (std::runtime_error &error) {
        throw std::runtime_error("ERROR IN: open file in logger constructor: " + std::string(error.what()));
    }
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

void Logger::create_new_log(const std::string &log_info, std::thread::id thread_id) {
    lock_logs_mutex();
    std::stringstream id_stream;
    try {
        id_stream << thread_id;
        std::string id_string = id_stream.str();
        logs_file << "Thread id: " + id_string + ". " + log_info << std::endl;
        std::cout << "Thread id: " + id_string + ". " + log_info << std::endl;
    }
    catch (std::runtime_error &error) {
        unlock_logs_mutex();
        throw std::runtime_error("ERROR IN: create_new_log: " + std::string(error.what()));
    }
    unlock_logs_mutex();
}
