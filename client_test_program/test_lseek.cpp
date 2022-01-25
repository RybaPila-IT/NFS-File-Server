#include <iostream>
#include <iomanip>
#include <cassert>

#include "test_lseek.h"

#define CREATE 0
#define READ   1
#define WRITE  2
#define READ_WRITE 3

TestLseek::TestLseek(const char *server_address, int port_number) : manager() {
    int desc;
    try {
        manager.mount(server_address, port_number);
        desc = manager.open(path_to_file, CREATE);
        manager.close(desc);
        desc = manager.open(path_to_file, WRITE);
        manager.write(desc, content.data(), content.size());
        manager.close(desc);
    } catch (std::runtime_error &err) {
        std::cerr << "CRITICAL ERROR: " << err.what() << "\n";
        exit(-1);
    }
}

void TestLseek::run_all_tests() {
    std::cout << "\n\n";
    std::cout << "**********************************************************************\n";
    std::cout << "********************** Starting lseek test suit **********************\n";
    std::cout << "**********************************************************************\n\n";

    test_lseek_zero_length();
    test_lseek_regular_length();
    test_lseek_out_of_range_length();
    test_lseek_negative_length();
    test_lseek_negative_out_of_range_length();

    std::cout << "\n**********************************************************************\n";
    std::cout << "********************** Lseek test suit finished **********************\n";
    std::cout << "**********************************************************************\n";
}

void TestLseek::test_lseek_zero_length() {
    std::string expected, got;
    int buffer_size = 10;
    char buffer[buffer_size];
    int desc, read_bytes;
    try {
        desc = manager.open(path_to_file, READ);
        manager.read(desc, buffer, buffer_size);
        manager.lseek(desc, 0);
        read_bytes = manager.read(desc, buffer, buffer_size);
        expected = "This is sa";
        got = std::string(buffer, read_bytes);
        assert(expected == got && "Messages mismatch with zero lseek length...");
        manager.close(desc);
    } catch (std::runtime_error &err) {
        std::cerr << "CRITICAL ERROR: " << err.what() << "\n";
        assert(false && "Unexpected error occurred...");
    }
    std::cout << std::left << std::setw(offset) << "Test zero length lseek" << "PASSED\n";
}

void TestLseek::test_lseek_regular_length() {
    std::string expected, got;
    int buffer_size = 10;
    char buffer[buffer_size];
    int desc, read_bytes;
    try {
        desc = manager.open(path_to_file, READ);
        manager.read(desc, buffer, buffer_size);
        manager.lseek(desc, 10);
        read_bytes = manager.read(desc, buffer, buffer_size);
        expected = "mple conte";
        got = std::string(buffer, read_bytes);
        assert(expected == got && "Messages mismatch with regular lseek length...");
        manager.close(desc);
    } catch (std::runtime_error &err) {
        std::cerr << "CRITICAL ERROR: " << err.what() << "\n";
        assert(false && "Unexpected error occurred...");
    }
    std::cout << std::left << std::setw(offset) << "Test regular length lseek" << "PASSED\n";
}

void TestLseek::test_lseek_out_of_range_length() {
    std::string expected, got;
    int buffer_size = 10;
    char buffer[buffer_size];
    int desc, read_bytes;
    try {
        desc = manager.open(path_to_file, READ);
        manager.read(desc, buffer, buffer_size);
        manager.lseek(desc, 1000);
        read_bytes = manager.read(desc, buffer, buffer_size);
        expected = "";
        got = std::string(buffer, read_bytes);
        assert(expected == got && "Messages mismatch with out-of-range lseek length...");
        manager.close(desc);
    } catch (std::runtime_error &err) {
        std::cerr << "CRITICAL ERROR: " << err.what() << "\n";
        assert(false && "Unexpected error occurred...");
    }
    std::cout << std::left << std::setw(offset) << "Test out-of-range length lseek" << "PASSED\n";
}

void TestLseek::test_lseek_negative_length() {
    std::string expected, got;
    int buffer_size = 10;
    char buffer[buffer_size];
    int desc, read_bytes;
    try {
        desc = manager.open(path_to_file, READ);
        manager.read(desc, buffer, buffer_size);
        manager.lseek(desc, 10000);
        manager.lseek(desc, -10);
        read_bytes = manager.read(desc, buffer, buffer_size);
        expected = "st file...";
        got = std::string(buffer, read_bytes);
        assert(expected == got && "Messages mismatch with negative lseek length...");
        manager.close(desc);
    } catch (std::runtime_error &err) {
        std::cerr << "CRITICAL ERROR: " << err.what() << "\n";
        assert(false && "Unexpected error occurred...");
    }
    std::cout << std::left << std::setw(offset) << "Test negative length lseek" << "PASSED\n";
}

void TestLseek::test_lseek_negative_out_of_range_length() {
    std::string expected, got;
    int buffer_size = 10;
    char buffer[buffer_size];
    int desc, read_bytes;
    try {
        desc = manager.open(path_to_file, READ);
        manager.read(desc, buffer, buffer_size);
        manager.lseek(desc, 15);
        manager.lseek(desc, -1000);
        read_bytes = manager.read(desc, buffer, buffer_size);
        expected = "This is sa";
        got = std::string(buffer, read_bytes);
        assert(expected == got && "Messages mismatch with negative out-of-range lseek length...");
        manager.close(desc);
    } catch (std::runtime_error &err) {
        std::cerr << "CRITICAL ERROR: " << err.what() << "\n";
        assert(false && "Unexpected error occurred...");
    }
    std::cout << std::left << std::setw(offset) << "Test negative put-of-range length lseek" << "PASSED\n";
}

