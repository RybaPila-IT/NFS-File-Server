#include "read_and_write_test.h"
#include <iostream>
#include <cassert>
#include <iomanip>

#define CREATE 0
#define READ   1
#define WRITE  2
#define READ_WRITE 3

TestWriteRead::TestWriteRead(const char *server_address, int port_number) {}(const char *server_address, int port_number) {
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

void TestWriteRead::run_all_tests() {
    std::cout << "\n\n";
    std::cout << "**************************************************\n";
    std::cout << "******* Starting write and read test suit ********\n";
    std::cout << "**************************************************\n\n";

    reset_test_file();

    // Test cases testing simple correct behaviour
    test_write_empty_file();
    test_normal_write();
    test_normal_read();
    test_normal_read_write();

    // Test cases testing exception throwing
    test_write_to_not_existing_desc();
    test_write_to_closed_desc();
    test_write_with_wrong_open_mode();
    test_write_while_different_file_opened();

    test_read_from_not_existing_desc();
    test_read_from_closed_desc();
    test_read_with_wrong_open_mode();
    test_read_while_different_file_opened();

    // Test cases testing two file descriptors on two FileSystemManagers

    //CHECK
    /*POSSIBLY COMPLETELY NOT NEEDED
    test_write_to_file_taken_by_reader();
    test_write_to_file_taken_by_writer();
    test_read_from_file_taken_by_reader();
    test_read_from_file_taken_by_writer();
    test_read_write_with_file_taken_by_reader();
    test_read_write_with_file_taken_by_writer();
    test_write_with_file_taken_by_write_reader();
    test_read_with_file_taken_by_write_reader();
    */

    test_mixed_order_read_then_write();
    test_mixed_order_write_then_read();
    test_mixed_order_read_then_write_reader();


    std::cout << "**************************************************\n";
    std::cout << "******* Write and read test suit finished ********\n";
    std::cout << "**************************************************\n";
}

void TestWriteRead::test_write_empty_file() {
    reset_test_file();
    try {
        desc = manager.open(path_to_existing_file, WRITE);
        std::string empty = "";
        manager.write(desc, empty.data(), empty.size());
        manager.close(desc);
        desc = manager.open(path_to_existing_file, READ);
        read_bytes = manager.read(desc, buffer, buffer_size);
        expected = "";
        got = std::string (buffer, read_bytes);
        assert(expected == got && "Messages mismatch with write empty file...");
        std::cout << std::left << std::setw(44) << "Test write empty file" << "PASSED\n";

    } catch (std::runtime_error &err) {
        std::cerr << "CRITICAL ERROR: " << err.what() << "\n";
        assert(false && "An error should not occur!");
    }
}

void TestWriteRead::reset_test_file() {
    try{
        desc = manager.open(path_to_existing_file, WRITE);
        manager.write(desc, default_file_data.data(), default_file_data.size())
        manager.close(desc);
    } catch (std::runtime_error& err) {
        std::cerr << err.what() << "\n";
        // Attempt to close the file if the test crashes.
        try {
            manager.close(desc);
        } catch (std::runtime_error& err) {
            std::cerr << "CRITICAL ERROR: " << err.what() << "\n";
        }
        assert(false && "An error should not occur!");
    }
    desc = -1;
    desc_2 = -1;
    std::cout << "\n test file reset\n";
}

void TestWriteRead::test_normal_write() {
    reset_test_file();
    try {
        desc = manager.open(path_to_existing_file, WRITE);
        std::string content = "Normal content";
        manager.write(desc, content.data(), content.size());
        manager.close(desc);
        desc = manager.open(path_to_existing_file, READ);
        read_bytes = manager.read(desc, buffer, buffer_size);
        expected = "Normal content";
        got = std::string(buffer, read_bytes);
        assert(expected == got && "Messages mismatch with write normal file...");
        std::cout << std::left << std::setw(44) << "Test write normal file " << "PASSED\n";

    } catch (std::runtime_error &err) {
        std::cerr << "CRITICAL ERROR: " << err.what() << "\n";
        assert(false && "An error should not occur!");
    }
}

void TestWriteRead::test_normal_read() {
    reset_test_file();
    try {
        desc = manager.open(path_to_existing_file, READ);
        read_bytes = manager.read(desc, buffer, buffer_size);
        expected = default_file_data;
        got = std::string (buffer, read_bytes);
        assert(expected == got && "Messages mismatch with read normal file...");
        std::cout << std::left << std::setw(44) << "Test read normal file " << "PASSED\n";

    } catch (std::runtime_error &err) {
        std::cerr << "CRITICAL ERROR: " << err.what() << "\n";
        assert(false && "An error should not occur!");
    }
}

void TestWriteRead::test_normal_read_write() {
    reset_test_file();
    try {

        desc = manager.open(path_to_existing_file, READ_WRITE);
        read_bytes = manager.read(desc, buffer, buffer_size);
        expected = default_file_data;
        got = std::string (buffer, read_bytes);
        assert(expected == got && "Messages mismatch with read_write read...");
        std::string new_content = "New content";
        manager.write(desc, new_content.data(), new_content.size());
        read_bytes = manager.read(desc, buffer, buffer_size);
        expected = new_content;
        got = std::string (buffer, read_bytes);
        assert(expected == got && "Messages mismatch with read_write read after write...");
        std::cout << std::left << std::setw(44) << "Test read_write a file " << "PASSED\n";

    } catch (std::runtime_error &err) {
        std::cerr << "CRITICAL ERROR: " << err.what() << "\n";
        assert(false && "An error should not occur!");
    }
}

void TestWriteRead::test_write_to_not_existing_desc() {
    bool was_exception_thrown = false;
    try {
        desc = non_existing_desc;
        std::string any_content = "Anything";
        manager.write(desc, any_content.data(), any_content.size());
        manager.close(desc);
    } catch (std::runtime_error &err) {
        was_exception_thrown = true;
    }
    if (!was_exception_thrown) {
        assert(false && "Write should have thrown an exception in write to not existing descriptor...");
    }
    std::cout << std::left << std::setw(offset) << "Test write to not existing descriptor " << "PASSED\n";
}

void TestWriteRead::test_write_to_closed_desc() {
    bool was_exception_thrown = false;
    try {
        desc = manager.open(path_to_existing_file, WRITE);
        manager.close(desc);
        std::string any_content = "Anything";
        manager.write(desc, any_content.data(), any_content.size());
    } catch (std::runtime_error &err) {
        was_exception_thrown = true;
    }
    if (!was_exception_thrown) {
        assert(false && "Write should have thrown an exception in write to closed descriptor...");
    }
    std::cout << std::left << std::setw(offset) << "Test write to closed descriptor " << "PASSED\n";
}

void TestWriteRead::test_write_with_wrong_open_mode() {
    bool was_exception_thrown = false;
    try {
        desc = manager.open(path_to_existing_file, READ);
        std::string any_content = "Anything";
        manager.write(desc, any_content.data(), any_content.size());
        manager.close(desc);
    } catch (std::runtime_error &err) {
        was_exception_thrown = true;
    }
    if (!was_exception_thrown) {
        assert(false && "Write should have thrown an exception in write with wrong open mode...");
    }
    std::cout << std::left << std::setw(offset) << "Test write with wrong open mode " << "PASSED\n";
}
//CHECK
void TestWriteRead::test_write_while_different_file_opened() {}

void TestWriteRead::test_read_from_not_existing_desc() {
    bool was_exception_thrown = false;
    try {
        desc = non_existing_desc;
        read_bytes = manager.read(desc, buffer, buffer_size);
        manager.close(desc);
    } catch (std::runtime_error &err) {
        was_exception_thrown = true;
    }
    if (!was_exception_thrown) {
        assert(false && "Read should have thrown an exception in read from not existing desc...");
    }
    std::cout << std::left << std::setw(offset) << "Test read from not existing desc " << "PASSED\n";
}

void TestWriteRead::test_read_from_closed_desc() {
    bool was_exception_thrown = false;
    try {
        desc = manager.open(path_to_existing_file, READ);
        manager.close(desc);
        read_bytes = manager.read(desc, buffer, buffer_size);
    } catch (std::runtime_error &err) {
        was_exception_thrown = true;
    }
    if (!was_exception_thrown) {
        assert(false && "Read should have thrown an exception in read from closed descriptor...");
    }
    std::cout << std::left << std::setw(offset) << "Test read from closed descriptor" << "PASSED\n";
}

void TestWriteRead::test_read_with_wrong_open_mode() {
    bool was_exception_thrown = false;
    try {
        desc = manager.open(path_to_existing_file, WRITE);
        read_bytes = manager.read(desc, buffer, buffer_size);
        manager.close(desc);
    } catch (std::runtime_error &err) {
        was_exception_thrown = true;
    }
    if (!was_exception_thrown) {
        assert(false && "Read should have thrown an exception in read with wrong open mode...");
    }
    std::cout << std::left << std::setw(offset) << "Test read with wrong open mode" << "PASSED\n";
}

//CHECK
void TestWriteRead::read_while_different_file_opened() {}

void TestWriteRead::test_mixed_order_read_then_write() {
    reset_test_file();
    try {
        desc = manager.open(path_to_existing_file, READ);
        desc_2 = manager_second.open(path_to_existing_file, WRITE);

        read_bytes = manager.read(desc, buffer, buffer_size);
        expected = default_file_data;
        got = std::string (buffer, read_bytes);
        assert(expected == got && "Messages mismatch with mixed_order read then write, first read...");

        std::string new_content = "New content";
        manager_second.write(desc_2, new_content.data(), new_content.size());
        read_bytes = manager.read(desc, buffer, buffer_size);
        expected = new_content;
        got = std::string (buffer, read_bytes);
        assert(expected == got && "Messages mismatch with mixed_order read then write, second read...");
        std::cout << std::left << std::setw(44) << "Test mixed_order read then write " << "PASSED\n";

    } catch (std::runtime_error &err) {
        std::cerr << "CRITICAL ERROR: " << err.what() << "\n";
        assert(false && "An error should not occur!");
    }
}

//CHECK może być nie potrzebny
void TestWriteRead::test_mixed_order_write_then_read(){
    reset_test_file();
    try {
        desc = manager.open(path_to_existing_file, READ);
        desc_2 = manager_second.open(path_to_existing_file, WRITE);

        std::string new_content = "New content";
        manager_second.write(desc_2, new_content.data(), new_content.size());
        read_bytes = manager.read(desc, buffer, buffer_size);
        expected = new_content;
        got = std::string (buffer, read_bytes);
        assert(expected == got && "Messages mismatch with mixed_order write then read...");

        std::cout << std::left << std::setw(44) << "Test mixed_order write then read " << "PASSED\n";

    } catch (std::runtime_error &err) {
        std::cerr << "CRITICAL ERROR: " << err.what() << "\n";
        assert(false && "An error should not occur!");
    }
}

void TestWriteRead::test_mixed_order_read_then_write_reader(){
    reset_test_file();
    try {
        desc = manager.open(path_to_existing_file, READ);
        desc_2 = manager_second.open(path_to_existing_file, READ_WRITE);

        read_bytes = manager.read(desc, buffer, buffer_size);
        expected = default_file_data;
        got = std::string (buffer, read_bytes);
        assert(expected == got && "Messages mismatch with mixed_order read then read_write, first read...");

        read_bytes = manager_second.read(desc_2, buffer, buffer_size);
        expected = default_file_data;
        got = std::string (buffer, read_bytes);
        assert(expected == got && "Messages mismatch with mixed_order read then read_write, second read...");

        std::string new_content = "New content";
        manager_second.write(desc_2, new_content.data(), new_content.size());
        read_bytes = manager.read(desc, buffer, buffer_size);
        expected = new_content;
        got = std::string (buffer, read_bytes);
        assert(expected == got && "Messages mismatch with mixed_order read then read_write, third read...");

        read_bytes = manager_second.read(desc_2, buffer, buffer_size);
        got = std::string (buffer, read_bytes);
        assert(expected == got && "Messages mismatch with mixed_order read then read_write, fourth read...");

        std::cout << std::left << std::setw(44) << "Test mixed_order read then read_write " << "PASSED\n";

    } catch (std::runtime_error &err) {
        std::cerr << "CRITICAL ERROR: " << err.what() << "\n";
        assert(false && "An error should not occur!");
    }
}


