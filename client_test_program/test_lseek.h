#ifndef CLIENT_TESTS_H
#define CLIENT_TESTS_H

#include "file_system_manager.h"

class TestLseek {

private:
    FileSystemManager manager;

    // For better visuals logging purpose
    int offset = 64;

    // test data
    std::string path_to_file = "test_lseek.test_file";
    std::string content = "This is sample content which will be saved to test file...";

    void test_lseek_zero_length();
    void test_lseek_regular_length();
    void test_lseek_out_of_range_length();
    void test_lseek_negative_length();
    void test_lseek_negative_out_of_range_length();

public:
    TestLseek(const char* server_address, int port_number);
    void run_all_tests();
};


#endif //CLIENT_TESTS_H
