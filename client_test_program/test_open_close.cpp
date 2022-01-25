#include <iostream>
#include "test_open_close.h"
#include <cassert>
#include <iomanip>

#define CREATE 0
#define READ   1
#define WRITE  2
#define READ_WRITE 3


TestOpenClose::TestOpenClose(const char *server_address, int port_number) {
    try {
        manager.mount(server_address, port_number);
        manager_second.mount(server_address, port_number);
        int desc = manager.open(path_to_existing_file, CREATE);
        manager.close(desc);
    } catch (std::runtime_error &err) {
        std::cerr << "CRITICAL ERROR: " << err.what() << "\n";
        exit(2);
    }
}

void TestOpenClose::run_all_tests() {
    std::cout << "\n\n";
    std::cout << "**********************************************************************\n";
    std::cout << "***************** Starting open and close test suit ******************\n";
    std::cout << "**********************************************************************\n\n";

    test_open_close_in_every_mode();
    test_open_close_with_writer_lock();
    test_create_file();
    test_open_with_wrong_mode();
    test_open_with_wrong_path();
    test_open_already_opened_file();
    test_close_with_non_existing_desc();
    test_close_with_already_closed_desc();
    test_open_one_file_two_times_create_mode();
    test_open_one_file_two_times_read_mode();
    test_open_one_file_two_times_write_mode();
    test_open_one_file_two_times_readwrite_mode();
    test_open_one_file_first_read_then_write_mode();
    test_open_one_file_first_write_then_read_mode();
    test_close_not_your_descriptor();

    std::cout << "\n**********************************************************************\n";
    std::cout << "***************** Open and close test suit finished ******************\n";
    std::cout << "**********************************************************************\n";
}

void TestOpenClose::test_open_close_in_every_mode() {
    int desc;
    try {
        desc = manager.open(path_to_existing_file, CREATE);
        manager.close(desc);
        desc = manager.open(path_to_existing_file, READ);
        manager.close(desc);
        desc = manager.open(path_to_existing_file, WRITE);
        manager.close(desc);
        desc = manager.open(path_to_existing_file, READ_WRITE);
        manager.close(desc);
    } catch (std::runtime_error &err) {
        std::cerr << "CRITICAL ERROR: " << err.what() << "\n";
        assert(false && "An error should not occur!");
    }
    std::cout << std::left << std::setw(offset) << "Test open close in every mode" << "PASSED\n";
}

void TestOpenClose::test_open_close_with_writer_lock() {
    int desc;
    try {
        desc = manager.open(path_to_existing_file, WRITE);
        manager.close(desc);
        desc = manager.open(path_to_existing_file, READ);
        manager.close(desc);
        desc = manager.open(path_to_existing_file, WRITE);
        manager.close(desc);
        desc = manager.open(path_to_existing_file, READ_WRITE);
        manager.close(desc);
        desc = manager.open(path_to_existing_file, CREATE);
        manager.close(desc);
    } catch (std::runtime_error &err) {
        std::cerr << "CRITICAL ERROR: " << err.what() << "\n";
        assert(false && "An error should not occur!");
    }
    std::cout << std::left << std::setw(offset) << "Test open close in every mode with write first" << "PASSED\n";
}

void TestOpenClose::test_create_file() {
    int desc;
    try {
        desc = manager.open(path_to_file_for_creation, CREATE);
        manager.close(desc);
        desc = manager.open(path_to_file_for_creation, CREATE);
        manager.close(desc);
    } catch (std::runtime_error &err) {
        std::cerr << "CRITICAL ERROR: " << err.what() << "\n";
        assert(false && "An error should not occur!");
    }
    std::cout << std::left << std::setw(offset) << "Test open in creation mode" << "PASSED\n";
}

void TestOpenClose::test_open_with_wrong_mode() {
    bool was_exception_thrown = false;
    try {
        manager.open(path_to_existing_file, wrong_open_mode);
    } catch (std::runtime_error &err) {
        was_exception_thrown = true;
    }
    assert(was_exception_thrown && "Open should have thrown an exception in open with bad open mode...");
    std::cout << std::left << std::setw(offset) << "Test open with wrong open mode" << "PASSED\n";
}

void TestOpenClose::test_open_with_wrong_path() {
    bool was_exception_thrown = false;
    try {
        manager.open(path_to_non_existing_file, READ);
    } catch (std::runtime_error &err) {
        was_exception_thrown = true;
    }
    assert(was_exception_thrown && "Open should have thrown an exception in open with bad path...");
    std::cout << std::left << std::setw(offset) << "Test open with bad path" << "PASSED\n";
}

void TestOpenClose::test_close_with_non_existing_desc() {
    bool was_exception_thrown = false;
    try {
        manager.close(non_existing_desc);
    } catch (std::runtime_error &err) {
        was_exception_thrown = true;
    }
    assert(was_exception_thrown && "Close should have thrown an exception in close with bad descriptor...");
    std::cout << std::left << std::setw(offset) << "Test close with bad descriptor" << "PASSED\n";
}

void TestOpenClose::test_close_with_already_closed_desc() {
    int desc;
    bool was_exception_thrown = false;
    try {
        desc = manager.open(path_to_existing_file, READ);
        manager.close(desc);
        manager.close(desc);
    } catch (std::runtime_error &err) {
        was_exception_thrown = true;
    }
    assert(was_exception_thrown && "Close should have thrown an exception in close with already closed descriptor...");
    std::cout << std::left << std::setw(offset) << "Test close with already closed descriptor" << "PASSED\n";
}

void TestOpenClose::test_open_already_opened_file() {
    int desc;
    bool was_exception_thrown = false;
    try {
        desc = manager.open(path_to_existing_file, READ);
        manager.open(path_to_existing_file, READ);
    } catch (std::runtime_error &err) {
        was_exception_thrown = true;
    }
    assert(was_exception_thrown && "Open should have thrown an exception since file is already opened...");
    try {
        manager.close(desc);
    } catch (std::runtime_error& err) {
        assert(false && "Error while closing a file...");
    }
    std::cout << std::left << std::setw(offset) << "Test open with already opened file" << "PASSED\n";
}

void TestOpenClose::test_open_one_file_two_times_create_mode() {
    int desc_1, desc_2;
    try {
        desc_1 = manager.open(path_to_existing_file, CREATE);
        desc_2 = manager_second.open(path_to_existing_file, CREATE);
        manager.close(desc_1);
        manager_second.close(desc_2);
    } catch (std::runtime_error &err) {
        std::cerr << "CRITICAL ERROR: " << err.what() << "\n";
        assert(false && "An error occurred when creating same file in two FileSystemManagers...");
    }
    std::cout << std::left << std::setw(offset) << "Test open one file on two FSMs in create mode" << "PASSED\n";
}

void TestOpenClose::test_open_one_file_two_times_read_mode() {
    int desc_1, desc_2;
    try {
        desc_1 = manager.open(path_to_existing_file, READ);
        desc_2 = manager_second.open(path_to_existing_file, READ);
        manager.close(desc_1);
        manager_second.close(desc_2);
    } catch (std::runtime_error &err) {
        std::cerr << "CRITICAL ERROR: " << err.what() << "\n";
        assert(false && "An error occurred when reading same file in two FileSystemManagers...");
    }
    std::cout << std::left << std::setw(offset) << "Test open one file on two FSMs in read mode" << "PASSED\n";
}

void TestOpenClose::test_open_one_file_two_times_write_mode() {
    int desc_1 = -1, desc_2 = -1;
    bool was_exception_thrown = false;
    try {
        desc_1 = manager.open(path_to_existing_file, WRITE);
        desc_2 = manager_second.open(path_to_existing_file, WRITE);
    } catch (std::runtime_error &err) {
        was_exception_thrown = true;
    }
    assert(was_exception_thrown && "Open should have thrown an exception in open with file opened in write mode...");
    try {
        if (desc_1 != -1)
            manager.close(desc_1);
        if (desc_2 != -1)
            manager_second.close(desc_2);
    } catch (std::runtime_error& err) {
        std::cerr << "CRITICAL ERROR: " << err.what() << "\n";
        assert(false && "An error occurred when closing file in two FileSystemManagers...");
    }
    std::cout << std::left << std::setw(offset) << "Test open one file on two FSMs in write mode" << "PASSED\n";
}

void TestOpenClose::test_open_one_file_two_times_readwrite_mode() {
    int desc_1 = -1, desc_2 = -1;
    bool was_exception_thrown = false;
    try {
        desc_1 = manager.open(path_to_existing_file, READ_WRITE);
        desc_2 = manager_second.open(path_to_existing_file, READ_WRITE);
    } catch (std::runtime_error &err) {
        was_exception_thrown = true;
    }
    assert(was_exception_thrown && "Open should have thrown an exception in open with file opened in read/write mode...");
    try {
        if (desc_1 != -1)
            manager.close(desc_1);
        if (desc_2 != -1)
            manager_second.close(desc_2);
    } catch (std::runtime_error& err) {
        std::cerr << "CRITICAL ERROR: " << err.what() << "\n";
        assert(false && "An error occurred when closing file in two FileSystemManagers...");
    }
    std::cout << std::left << std::setw(offset) << "Test open one file on two FSMs in read/write mode" << "PASSED\n";
}

void TestOpenClose::test_open_one_file_first_read_then_write_mode() {
    int desc_1, desc_2;
    try {
        desc_1 = manager.open(path_to_existing_file, READ);
        desc_2 = manager_second.open(path_to_existing_file, WRITE);
        manager.close(desc_1);
        manager_second.close(desc_2);
    } catch (std::runtime_error &err) {
        std::cerr << "CRITICAL ERROR: " << err.what() << "\n";
        assert(false &&
               "An error occurred when opening same file in two FileSystemManagers in write and then read mode...");
    }
    std::cout << std::left << std::setw(offset) << "Test open one file on two FSMs in read and then write mode"
              << "PASSED\n";
}

void TestOpenClose::test_open_one_file_first_write_then_read_mode() {
    int desc_1 = -1, desc_2 = -1;
    bool was_exception_thrown = false;
    try {
        desc_1 = manager.open(path_to_existing_file, WRITE);
        desc_2 = manager_second.open(path_to_existing_file, READ);
    } catch (std::runtime_error &err) {
        was_exception_thrown = true;
    }
    assert(was_exception_thrown && "Open should have thrown an exception with file opened in read mode after write mode...");
    try {
        if (desc_1 != -1)
            manager.close(desc_1);
        if (desc_2 != -1)
            manager_second.close(desc_2);
    } catch (std::runtime_error& err) {
        std::cerr << "CRITICAL ERROR: " << err.what() << "\n";
        assert(false && "An error occurred when closing file in two FileSystemManagers...");
    }
    std::cout << std::left << std::setw(offset) << "Test open one file on two FSMs in write mode then read mode"
              << "PASSED\n";
}

void TestOpenClose::test_close_not_your_descriptor() {
    int desc_1 = -1, desc_2 = -1;
    bool was_exception_thrown = false;
    try {
        desc_1 = manager.open(path_to_existing_file, READ);
        desc_2 = manager_second.open(path_to_existing_file, READ);
        manager.close(desc_2);
    } catch (std::runtime_error &err) {
        was_exception_thrown = true;
    }
    assert(was_exception_thrown && "Close should have thrown an exception in close with file descriptor not opened by him...");
    try {
        if (desc_1 != -1)
            manager.close(desc_1);
        if (desc_2 != -1)
            manager_second.close(desc_2);
    } catch (std::runtime_error& err) {
        std::cerr << "CRITICAL ERROR: " << err.what() << "\n";
        assert(false && "An error occurred when closing file in two FileSystemManagers...");
    }
    std::cout << std::left << std::setw(offset) << "Test close not your descriptor" << "PASSED\n";
}
