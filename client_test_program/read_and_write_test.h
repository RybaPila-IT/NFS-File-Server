#ifndef NFS_FILE_SERVER_READ_AND_WRITE_TEST_H
#define NFS_FILE_SERVER_READ_AND_WRITE_TEST_H
#include "file_system_manager.h"

class TestWriteRead {
    FileSystemManager manager;
    FileSystemManager manager_second;

    // test data
    std::string path_to_existing_file = "test_write_read.test_file";
    std::string path_to_second_existing_file = "test_write_read_second.test_file";
    std::string default_file_data = "default test data";
    std::string expected, got;
    int buffer_size = 100;
    char buffer[buffer_size];
    int desc = -1, desc_2 = -1, read_bytes;
    int non_existing_desc = 100;

    void reset_test_file();

    // Test cases testing simple correct behaviour
    void test_write_empty_file();
    void test_normal_write();
    void test_normal_read();
    void test_normal_read_write();

    // Test cases testing exception throwing
    void test_write_to_not_existing_desc();
    void test_write_to_closed_desc();
    void test_write_with_wrong_open_mode();
    void test_write_while_different_file_opened();

    void test_read_from_not_existing_desc();
    void test_read_from_closed_desc();
    void test_read_with_wrong_open_mode();
    void test_read_while_different_file_opened();

    // Test cases testing two file descriptors on two FileSystemManagers

    //CHECK
    /*POSSIBLY COMPLETELY NOT NEEDED
    void test_write_to_file_taken_by_reader();
    void test_write_to_file_taken_by_writer();
    void test_read_from_file_taken_by_reader();
    void test_read_from_file_taken_by_writer();
    void test_read_write_with_file_taken_by_reader();
    void test_read_write_with_file_taken_by_writer();
    void test_write_with_file_taken_by_write_reader();
    void test_read_with_file_taken_by_write_reader();
    */

    void test_mixed_order_read_then_write();
    void test_mixed_order_write_then_read();
    void test_mixed_order_read_then_write_reader();


public:
    TestWriteRead(const char* server_address, int port_number);
    void run_all_tests();
};


#endif //NFS_FILE_SERVER_READ_AND_WRITE_TEST_H
