#include <cassert>
#include <iomanip>

#include "test_fstat.h"
#include "iostream"

#define CREATE 0
#define READ   1
#define WRITE  2
#define READ_WRITE 3

TestFstat::TestFstat(const char *server_address, int port_number) {
    try {
        manager.mount(server_address, port_number);
        manager_second.mount(server_address, port_number);
        desc = manager.open(path_to_existing_file, CREATE);
        manager.close(desc);
    } catch (std::runtime_error &err) {
        std::cerr << "CRITICAL ERROR: " << err.what() << "\n";
        exit(-1);
    }
}

void TestFstat::run_all_tests() {
    std::cout << "\n\n";
    std::cout << "**********************************************************************\n";
    std::cout << "********************** Starting fstat test suit **********************\n";
    std::cout << "**********************************************************************\n\n";

    test_fstat_existing_file();
    test_fstat_non_existent_descriptor();
    test_fstat_with_two_clients();

    std::cout << "\n**********************************************************************\n";
    std::cout << "********************* Lseek fstat suit finished **********************\n";
    std::cout << "**********************************************************************\n";
}

void TestFstat::test_fstat_existing_file() {
    std::string expected, got_head, got_tail, got;
    try {
        desc = manager.open(path_to_existing_file, READ);
        expected = "FSTAT INFO";
        got = manager.fstat(desc);
        got_head = got.substr(0, 10);
        got_tail = got.substr(got.length() - 11, 10);
        assert((expected == got_tail) && (expected == got_head) &&
               "Messages mismatch with performing fstat on existing file...");
        manager.close(desc);
    } catch (std::runtime_error &err) {
        std::cerr << "CRITICAL ERROR: " << err.what() << "\n";
        assert(false && "Unexpected error occurred...");
    }
    std::cout << std::left << std::setw(offset) << "Test existing file fstat" << "PASSED\n";
}

void TestFstat::test_fstat_non_existent_descriptor() {
    bool was_exception_thrown = false;
    try {
        desc = manager.open(path_to_existing_file, READ);
        manager.fstat(non_existing_desc);
    } catch (std::runtime_error &err) {
        manager.close(desc);
        was_exception_thrown = true;
    }
    assert(was_exception_thrown && "Fstat should have thrown an exception in non existent descriptor test...");
    std::cout << std::left << std::setw(offset) << "Test non existent descriptor fstat" << "PASSED\n";
}

void TestFstat::test_fstat_with_two_clients() {
    std::string expected, got, got_second;
    std::string got_head, got_tail, got_second_head, got_second_tail;
    try {
        desc = manager.open(path_to_existing_file, READ);
        desc_second = manager_second.open(path_to_existing_file, READ);
        expected = "FSTAT INFO";
        got = manager.fstat(desc);
        got_second = manager_second.fstat(desc_second);
        got_head = got.substr(0, 10);
        got_tail = got.substr(got.length() - 11, 10);
        got_second_head = got_second.substr(0, 10);
        got_second_tail = got_second.substr(got_second.length() - 11, 10);
        assert((expected == got_tail && expected == got_head) && (expected == got_second_tail && expected == got_second_head) &&
               "Messages mismatch with performing fstat by two clients...");
        manager.close(desc);
        manager_second.close(desc_second);
    } catch (std::runtime_error &err) {
        std::cerr << "CRITICAL ERROR: " << err.what() << "\n";
        assert(false && "An error should not occur!");
    }
    std::cout << std::left << std::setw(offset) << "Test performing fstat by two clients" << "PASSED\n";
}
