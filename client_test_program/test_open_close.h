#ifndef CLIENT_TEST_PROGRAM_TEST_OPEN_CLOSE_H
#define CLIENT_TEST_PROGRAM_TEST_OPEN_CLOSE_H

#include "file_system_manager.h"

class TestOpenClose {
    FileSystemManager manager;
    FileSystemManager manager_second;

    // For better visuals logging purpose
    int offset = 64;

    // test data
    std::string path_to_existing_file = "test_open_close.test_file";
    std::string path_to_non_existing_file = "this_file_can_never_exist.test_file";
    std::string path_to_file_for_creation = "test_create_this_file.test_file";

    int wrong_open_mode = 100;
    int non_existing_desc = 100;

    // Test cases testing simple correct behaviour
    void test_open_close_in_every_mode();
    void test_open_close_with_writer_lock();
    void test_create_file();

    // Test cases testing exception throwing
    void test_open_with_wrong_mode();
    void test_open_with_wrong_path();
    void test_open_already_opened_file();
    void test_close_with_non_existing_desc();
    void test_close_with_already_closed_desc();

    // Test cases testing two file descriptors on two FileSystemManagers
    void test_open_one_file_two_times_create_mode();
    void test_open_one_file_two_times_read_mode();
    void test_open_one_file_two_times_write_mode();
    void test_open_one_file_two_times_readwrite_mode();
    void test_open_one_file_first_read_then_write_mode();
    void test_open_one_file_first_write_then_read_mode();
    void test_close_not_your_descriptor();

public:
    TestOpenClose(const char* server_address, int port_number);
    void run_all_tests();
};


#endif //CLIENT_TEST_PROGRAM_TEST_OPEN_CLOSE_H
