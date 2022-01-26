#ifndef SERVER_TEST_FSTAT_H
#define SERVER_TEST_FSTAT_H
#include "file_system_manager.h"


class TestFstat {
    FileSystemManager manager;
    FileSystemManager manager_second;

    // For better visuals logging purpose
    int offset = 64;

    // test data
    std::string path_to_existing_file = "test_fstat.test_file";
    int desc = -1, desc_second = -1;
    int non_existing_desc = 100;

    void test_fstat_existing_file();

    void test_fstat_non_existent_descriptor();

    void test_fstat_with_two_clients();

public:
    TestFstat(const char* server_address, int port_number);
    void run_all_tests();
};


#endif //SERVER_TEST_FSTAT_H
