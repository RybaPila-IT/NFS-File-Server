#include "test_read_and_write.h"
#include <iostream>
#include <cassert>
#include <iomanip>

#define CREATE 0
#define READ   1
#define WRITE  2
#define READ_WRITE 3

TestWriteRead::TestWriteRead(const char *server_address, int port_number) {
    try {
        manager.mount(server_address, port_number);
        manager_second.mount(server_address, port_number);
        int desc = manager.open(path_to_existing_file, CREATE);
        manager.close(desc);
        desc = manager.open(path_to_second_existing_file, CREATE);
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

    // Test cases testing basic simple correct behaviour
    test_write_empty_file();
    test_normal_write();
    test_normal_read();
    test_normal_read_write();

    // Test cases testing lseek interactions
    test_write_with_lseek();
    test_read_with_lseek();
    test_read_write_with_lseek();

    // Test cases testing multiple descriptors on one FileSystemManager
    test_write_while_different_file_opened();
    test_read_while_different_file_opened();

    // Test cases testing exception throwing
    test_write_to_not_existing_desc();
    test_write_to_closed_desc();
    test_write_with_wrong_open_mode();

    test_read_from_not_existing_desc();
    test_read_from_closed_desc();
    test_read_with_wrong_open_mode();


    // Test cases testing two file descriptors on two FileSystemManagers
    test_write_to_file_taken_by_reader();
    test_read_from_file_taken_by_reader();
    test_read_write_with_file_taken_by_reader();

    test_write_to_file_taken_by_writer();
    test_read_from_file_taken_by_writer();
    test_read_write_with_file_taken_by_writer();

    test_write_with_file_taken_by_write_reader();
    test_read_with_file_taken_by_write_reader();


    // Test cases testing two file descriptors on two FileSystemManagers operating on a single file in a mixed order
    test_mixed_order_read_then_write();
    test_mixed_order_write_then_read();
    test_mixed_order_read_then_write_reader();

    std::cout << "\n**************************************************\n";
    std::cout << "******* Write and read test suit finished ********\n";
    std::cout << "**************************************************\n";
}

void TestWriteRead::reset_test_file() {
    try {
        desc = manager.open(path_to_existing_file, WRITE);
        manager.write(desc, default_file_data.data(), default_file_data.size());
        manager.close(desc);
        desc = manager.open(path_to_second_existing_file, WRITE);
        manager.write(desc, default_file_data.data(), default_file_data.size());
        manager.close(desc);

    } catch (std::runtime_error &err) {
        std::cerr << err.what() << "\n";
        try {
            manager.close(desc);
        } catch (std::runtime_error &err) {
            std::cerr << "CRITICAL ERROR: " << err.what() << "\n";
        }
        assert(false && "An error should not occur!");
    }
    desc = -1;
    desc_2 = -1;
}

// Test cases testing basic simple correct behaviour
void TestWriteRead::test_write_empty_file() {
    reset_test_file();
    try {
        char buffer[buffer_size];
        desc = manager.open(path_to_existing_file, WRITE);
        std::string empty = "";
        manager.write(desc, empty.data(), empty.size());
        manager.close(desc);
        desc = manager.open(path_to_existing_file, READ);
        read_bytes = manager.read(desc, buffer, buffer_size);
        expected = "";
        got = std::string(buffer, read_bytes);
        assert(expected == got && "Messages mismatch with write empty file...");
        manager.close(desc);
        std::cout << std::left << std::setw(offset) << "Test write empty file" << "PASSED\n";

    } catch (std::runtime_error &err) {
        std::cerr << err.what() << "\n";
        try {
            manager.close(desc);
        } catch (std::runtime_error &err) {
            std::cerr << "CRITICAL ERROR: " << err.what() << "\n";
        }
        assert(false && "An error should not occur!");
    }
}

void TestWriteRead::test_normal_write() {
    reset_test_file();
    try {
        char buffer[buffer_size];
        desc = manager.open(path_to_existing_file, WRITE);
        std::string content = "Normal content";
        manager.write(desc, content.data(), content.size());
        manager.close(desc);
        desc = manager.open(path_to_existing_file, READ);
        read_bytes = manager.read(desc, buffer, buffer_size);
        expected = "Normal content";
        got = std::string(buffer, read_bytes);
        assert(expected == got && "Messages mismatch with write normal file...");
        manager.close(desc);
        std::cout << std::left << std::setw(offset) << "Test write normal file " << "PASSED\n";

    } catch (std::runtime_error &err) {
        std::cerr << "CRITICAL ERROR: " << err.what() << "\n";
        try {
            manager.close(desc);
        } catch (std::runtime_error &err) {
            std::cerr << "CRITICAL ERROR: " << err.what() << "\n";
        }
        assert(false && "An error should not occur!");
    }
}

void TestWriteRead::test_normal_read() {
    reset_test_file();
    try {
        char buffer[buffer_size];
        desc = manager.open(path_to_existing_file, READ);
        read_bytes = manager.read(desc, buffer, buffer_size);
        expected = default_file_data;
        got = std::string(buffer, read_bytes);
        assert(expected == got && "Messages mismatch with read normal file...");
        manager.close(desc);
        std::cout << std::left << std::setw(offset) << "Test read normal file " << "PASSED\n";

    } catch (std::runtime_error &err) {
        std::cerr << "CRITICAL ERROR: " << err.what() << "\n";
        try {
            manager.close(desc);
        } catch (std::runtime_error &err) {
            std::cerr << "CRITICAL ERROR: " << err.what() << "\n";
        }
        assert(false && "An error should not occur!");
    }
}

void TestWriteRead::test_normal_read_write() {
    reset_test_file();
    try {
        char buffer[buffer_size];
        desc = manager.open(path_to_existing_file, READ_WRITE);
        read_bytes = manager.read(desc, buffer, buffer_size);
        expected = default_file_data;
        got = std::string(buffer, read_bytes);
        assert(expected == got && "Messages mismatch with read_write read...");
        std::string new_content = "New content longer for testing purposes";
        manager.write(desc, new_content.data(), new_content.size());
        read_bytes = manager.read(desc, buffer, buffer_size);
        expected = new_content;
        got = std::string(buffer, read_bytes);
        assert(expected == got && "Messages mismatch with read_write read after write...");
        manager.close(desc);
        std::cout << std::left << std::setw(offset) << "Test read_write a file " << "PASSED\n";

    } catch (std::runtime_error &err) {
        std::cerr << "CRITICAL ERROR: " << err.what() << "\n";
        try {
            manager.close(desc);
        } catch (std::runtime_error &err) {
            std::cerr << "CRITICAL ERROR: " << err.what() << "\n";
        }
        assert(false && "An error should not occur!");
    }
}

// Test cases testing lseek interactions
void TestWriteRead::test_write_with_lseek() {
    reset_test_file();
    try {
        char buffer[buffer_size];
        desc = manager.open(path_to_existing_file, WRITE);
        manager.lseek(desc, 8);
        std::string new_content = "New content longer for testing";
        manager.write(desc, new_content.data(), new_content.size());
        manager.close(desc);

        desc = manager.open(path_to_existing_file, READ);
        read_bytes = manager.read(desc, buffer, buffer_size);
        expected = "New content longer for testing";
        got = std::string(buffer, read_bytes);

        assert(expected == got && "Messages mismatch with write with lseek...");

        manager.close(desc);
        std::cout << std::left << std::setw(offset) << "Test write with lseek " << "PASSED\n";

    } catch (std::runtime_error &err) {
        std::cerr << "CRITICAL ERROR: " << err.what() << "\n";
        try {
            manager.close(desc);
        } catch (std::runtime_error &err) {
            std::cerr << "CRITICAL ERROR: " << err.what() << "\n";
        }
        assert(false && "An error should not occur!");
    }
}

void TestWriteRead::test_read_with_lseek() {
    reset_test_file();
    try {
        int lseek_length = 10;
        int temp_buffer_size = 10;
        char buffer[temp_buffer_size];
        desc = manager.open(path_to_existing_file, READ);
        read_bytes = manager.read(desc, buffer, temp_buffer_size);
        manager.lseek(desc, lseek_length);
        read_bytes = manager.read(desc, buffer, temp_buffer_size);
        expected = default_file_data.substr(lseek_length, temp_buffer_size);
        got = std::string(buffer, read_bytes);

        assert(expected == got && "Messages mismatch with read with lseek...");

        manager.close(desc);
        std::cout << std::left << std::setw(offset) << "Test read with lseek " << "PASSED\n";

    } catch (std::runtime_error &err) {
        std::cerr << "CRITICAL ERROR: " << err.what() << "\n";
        try {
            manager.close(desc);
        } catch (std::runtime_error &err) {
            std::cerr << "CRITICAL ERROR: " << err.what() << "\n";
        }
        assert(false && "An error should not occur!");
    }
}

void TestWriteRead::test_read_write_with_lseek() {
    reset_test_file();
    try {
        char buffer[buffer_size];
        desc = manager.open(path_to_existing_file, READ_WRITE);
        read_bytes = manager.read(desc, buffer, buffer_size);
        manager.lseek(desc, 8);
        read_bytes = manager.read(desc, buffer, buffer_size);
        got = std::string(buffer, read_bytes);
        expected = "test data";
        assert(expected == got && "Messages mismatch with read_write with lseek, first read...");

        std::string new_content = "New content longer for testing";
        manager.write(desc, new_content.data(), new_content.size());
        read_bytes = manager.read(desc, buffer, buffer_size);

        expected = "New content longer for testing";
        got = std::string(buffer, read_bytes);
        assert(expected == got && "Messages mismatch with read_write with lseek, second read...");

        manager.lseek(desc, -8);
        read_bytes = manager.read(desc, buffer, buffer_size);
        expected = "default New content longer for testing";
        got = std::string(buffer, read_bytes);

        assert(expected == got && "Messages mismatch with read_write with lseek, third read...");

        manager.close(desc);
        std::cout << std::left << std::setw(offset) << "Test write with lseek " << "PASSED\n";

    } catch (std::runtime_error &err) {
        std::cerr << "CRITICAL ERROR: " << err.what() << "\n";
        assert(false && "An error should not occur!");
    }
}

// Test cases testing multiple descriptors on one FileSystemManager
void TestWriteRead::test_write_while_different_file_opened() {
    reset_test_file();
    try {
        char buffer[buffer_size];
        desc = manager.open(path_to_existing_file, READ);
        desc_2 = manager.open(path_to_second_existing_file, WRITE);
        std::string new_content = "New content longer for testing";
        manager.write(desc_2, new_content.data(), new_content.size());
        manager.close(desc_2);
        manager.close(desc);

        desc = manager.open(path_to_second_existing_file, READ);
        read_bytes = manager.read(desc, buffer, buffer_size);
        expected = new_content;
        got = std::string(buffer, read_bytes);
        assert(expected == got && "Messages mismatch with write while different file is opened...");
        manager.close(desc);
        std::cout << std::left << std::setw(offset) << "Test write while different file is opened " << "PASSED\n";

    } catch (std::runtime_error &err) {
        std::cerr << "CRITICAL ERROR: " << err.what() << "\n";
        try {
            manager.close(desc);
        } catch (std::runtime_error &err) {
            std::cerr << "CRITICAL ERROR: " << err.what() << "\n";
        }
        assert(false && "An error should not occur!");
    }
}

void TestWriteRead::test_read_while_different_file_opened() {
    reset_test_file();
    try {
        char buffer[buffer_size];
        desc = manager.open(path_to_existing_file, READ);
        desc_2 = manager.open(path_to_second_existing_file, READ);
        read_bytes = manager.read(desc, buffer, buffer_size);
        expected = default_file_data;
        got = std::string(buffer, read_bytes);
        assert(expected == got && "Messages mismatch with read while different file is opened...");
        manager.close(desc);
        manager.close(desc_2);
        std::cout << std::left << std::setw(offset) << "Test read while different file is opened " << "PASSED\n";

    } catch (std::runtime_error &err) {
        std::cerr << "CRITICAL ERROR: " << err.what() << "\n";
        try {
            manager.close(desc);
            manager.close(desc_2);
        } catch (std::runtime_error &err) {
            std::cerr << "CRITICAL ERROR: " << err.what() << "\n";
        }
        assert(false && "An error should not occur!");
    }
}

// Test cases testing simple exception throwing
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
        try {
            manager.close(desc);
        } catch (std::runtime_error &err) {
            std::cerr << "CRITICAL ERROR: " << err.what() << "\n";
        }
        was_exception_thrown = true;
    }
    if (!was_exception_thrown) {
        assert(false && "Write should have thrown an exception in write with wrong open mode...");
    }
    std::cout << std::left << std::setw(offset) << "Test write with wrong open mode " << "PASSED\n";
}

void TestWriteRead::test_read_from_not_existing_desc() {
    bool was_exception_thrown = false;
    char buffer[buffer_size];
    try {
        desc = non_existing_desc;
        read_bytes = manager.read(desc, buffer, buffer_size);
        manager.close(desc);
    } catch (std::runtime_error &err) {
        try {
            manager.close(desc);
        } catch (std::runtime_error &err) {
            std::cerr << "CRITICAL ERROR: " << err.what() << "\n";
        }
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
        char buffer[buffer_size];
        desc = manager.open(path_to_existing_file, READ);
        manager.close(desc);
        read_bytes = manager.read(desc, buffer, buffer_size);
    } catch (std::runtime_error &err) {
        try {
            manager.close(desc);
        } catch (std::runtime_error &err) {
            std::cerr << "CRITICAL ERROR: " << err.what() << "\n";
        }
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
        char buffer[buffer_size];
        desc = manager.open(path_to_existing_file, WRITE);
        read_bytes = manager.read(desc, buffer, buffer_size);
        manager.close(desc);
    } catch (std::runtime_error &err) {
        try {
            manager.close(desc);
        } catch (std::runtime_error &err) {
            std::cerr << "CRITICAL ERROR: " << err.what() << "\n";
        }
        was_exception_thrown = true;
    }
    if (!was_exception_thrown) {
        assert(false && "Read should have thrown an exception in read with wrong open mode...");
    }
    std::cout << std::left << std::setw(offset) << "Test read with wrong open mode" << "PASSED\n";
}

// Test cases testing two file descriptors on two FileSystemManagers


void TestWriteRead::test_write_to_file_taken_by_reader() {
    reset_test_file();
    try {
        char buffer[buffer_size];
        desc = manager.open(path_to_existing_file, READ);
        desc_2 = manager_second.open(path_to_existing_file, WRITE);
        std::string new_content = "New content longer for testing";
        manager_second.write(desc_2, new_content.data(), new_content.size());
        manager_second.close(desc_2);

        desc_2 = manager_second.open(path_to_existing_file, READ);
        read_bytes = manager_second.read(desc_2, buffer, buffer_size);
        expected = new_content;
        got = std::string(buffer, read_bytes);
        assert(expected == got && "Messages mismatch with write to file taken by reader...");

        manager.close(desc);
        manager_second.close(desc_2);
        std::cout << std::left << std::setw(offset) << "Test write to file taken by reader " << "PASSED\n";

    } catch (std::runtime_error &err) {
        std::cerr << "CRITICAL ERROR: " << err.what() << "\n";
        try {
            manager.close(desc);
            manager.close(desc_2);
        } catch (std::runtime_error &err) {
            std::cerr << "CRITICAL ERROR: " << err.what() << "\n";
        }
        assert(false && "An error should not occur!");
    }
}

void TestWriteRead::test_read_from_file_taken_by_reader() {
    reset_test_file();
    try {
        char buffer[buffer_size];
        desc = manager.open(path_to_existing_file, READ);
        desc_2 = manager_second.open(path_to_existing_file, READ);
        read_bytes = manager_second.read(desc_2, buffer, buffer_size);
        expected = default_file_data;
        got = std::string(buffer, read_bytes);
        assert(expected == got && "Messages mismatch with read from file taken by reader...");
        manager.close(desc);
        manager_second.close(desc_2);
        std::cout << std::left << std::setw(offset) << "Test read from file taken by reader " << "PASSED\n";

    } catch (std::runtime_error &err) {
        std::cerr << "CRITICAL ERROR: " << err.what() << "\n";
        try {
            manager.close(desc);
            manager.close(desc_2);
        } catch (std::runtime_error &err) {
            std::cerr << "CRITICAL ERROR: " << err.what() << "\n";
        }
        assert(false && "An error should not occur!");
    }
}

void TestWriteRead::test_read_write_with_file_taken_by_reader() {
    reset_test_file();
    try {
        char buffer[buffer_size];
        desc = manager.open(path_to_existing_file, READ);
        desc_2 = manager_second.open(path_to_existing_file, READ_WRITE);
        std::string new_content = "New content longer for testing";
        manager_second.write(desc_2, new_content.data(), new_content.size());

        read_bytes = manager_second.read(desc_2, buffer, buffer_size);
        expected = new_content;
        got = std::string(buffer, read_bytes);
        assert(expected == got && "Messages mismatch with read_write to file taken by reader...");

        manager.close(desc);
        manager_second.close(desc_2);
        std::cout << std::left << std::setw(offset) << "Test read_write to file taken by reader " << "PASSED\n";

    } catch (std::runtime_error &err) {
        std::cerr << "CRITICAL ERROR: " << err.what() << "\n";
        try {
            manager.close(desc);
            manager.close(desc_2);
        } catch (std::runtime_error &err) {
            std::cerr << "CRITICAL ERROR: " << err.what() << "\n";
        }
        assert(false && "An error should not occur!");
    }
}

void TestWriteRead::test_write_to_file_taken_by_writer() {
    reset_test_file();
    bool was_exception_thrown = false;
    try {
        desc = manager.open(path_to_existing_file, WRITE);
        desc_2 = manager_second.open(path_to_existing_file, WRITE);
        std::string new_content = "Anything";
        manager_second.write(desc_2, new_content.data(), new_content.size());
        manager.close(desc);
        manager_second.close(desc_2);
    } catch (std::runtime_error &err) {
        try {
            manager.close(desc);
            manager_second.close(desc_2);
        } catch (std::runtime_error &err) {
            std::cerr << "CRITICAL ERROR: " << err.what() << "\n";
        }
        was_exception_thrown = true;
    }
    if (!was_exception_thrown) {
        assert(false && "Read should have thrown an exception in write to file taken by writer...");
    }
    std::cout << std::left << std::setw(offset) << "Test write to file taken by writer" << "PASSED\n";
}

void TestWriteRead::test_read_from_file_taken_by_writer() {
    reset_test_file();
    bool was_exception_thrown = false;
    try {
        char buffer[buffer_size];
        desc = manager.open(path_to_existing_file, WRITE);
        desc_2 = manager_second.open(path_to_existing_file, READ);
        read_bytes = manager_second.read(desc_2, buffer, buffer_size);
        manager.close(desc);
        manager_second.close(desc_2);
    } catch (std::runtime_error &err) {
        try {
            manager.close(desc);
            manager_second.close(desc_2);
        } catch (std::runtime_error &err) {
            std::cerr << "CRITICAL ERROR: " << err.what() << "\n";
        }
        was_exception_thrown = true;
    }
    if (!was_exception_thrown) {
        assert(false && "Read should have thrown an exception in read from file taken by writer...");
    }
    std::cout << std::left << std::setw(offset) << "Test read from file taken by writer" << "PASSED\n";
}

void TestWriteRead::test_read_write_with_file_taken_by_writer() {
    reset_test_file();
    bool was_exception_thrown = false;
    try {
        char buffer[buffer_size];
        desc = manager.open(path_to_existing_file, WRITE);
        desc_2 = manager_second.open(path_to_existing_file, READ_WRITE);
        std::string new_content = "Anything";
        manager_second.write(desc_2, new_content.data(), new_content.size());
        read_bytes = manager_second.read(desc_2, buffer, buffer_size);
        manager.close(desc);
        manager_second.close(desc_2);
    } catch (std::runtime_error &err) {
        try {
            manager.close(desc);
            manager_second.close(desc_2);
        } catch (std::runtime_error &err) {
            std::cerr << "CRITICAL ERROR: " << err.what() << "\n";
        }
        was_exception_thrown = true;
    }
    if (!was_exception_thrown) {
        assert(false && "Read should have thrown an exception in read_write to file taken by writer...");
    }
    std::cout << std::left << std::setw(offset) << "Test read_write to file taken by writer" << "PASSED\n";
}

void TestWriteRead::test_write_with_file_taken_by_write_reader() {
    reset_test_file();
    bool was_exception_thrown = false;
    try {
        desc = manager.open(path_to_existing_file, READ_WRITE);
        desc_2 = manager_second.open(path_to_existing_file, WRITE);
        std::string new_content = "Anything";
        manager_second.write(desc_2, new_content.data(), new_content.size());
        manager.close(desc);
        manager_second.close(desc_2);
    } catch (std::runtime_error &err) {
        try {
            manager.close(desc);
            manager_second.close(desc_2);
        } catch (std::runtime_error &err) {
            std::cerr << "CRITICAL ERROR: " << err.what() << "\n";
        }
        was_exception_thrown = true;
    }
    if (!was_exception_thrown) {
        assert(false && "Read should have thrown an exception in write to file taken by read_writer...");
    }
    std::cout << std::left << std::setw(offset) << "Test write to file taken by read_writer" << "PASSED\n";
}

void TestWriteRead::test_read_with_file_taken_by_write_reader() {
    reset_test_file();
    bool was_exception_thrown = false;
    try {
        char buffer[buffer_size];
        desc = manager.open(path_to_existing_file, READ_WRITE);
        desc_2 = manager_second.open(path_to_existing_file, READ);
        read_bytes = manager_second.read(desc_2, buffer, buffer_size);
        manager.close(desc);
        manager_second.close(desc_2);
    } catch (std::runtime_error &err) {
        try {
            manager.close(desc);
            manager_second.close(desc_2);
        } catch (std::runtime_error &err) {
            std::cerr << "CRITICAL ERROR: " << err.what() << "\n";
        }
        was_exception_thrown = true;
    }
    if (!was_exception_thrown) {
        assert(false && "Read should have thrown an exception in read from file taken by read_writer...");
    }
    std::cout << std::left << std::setw(offset) << "Test read from file taken by read_writer" << "PASSED\n";
}

void TestWriteRead::test_mixed_order_read_then_write() {
    reset_test_file();
    try {
        char buffer[buffer_size];

        desc = manager.open(path_to_existing_file, READ);
        desc_2 = manager_second.open(path_to_existing_file, WRITE);

        read_bytes = manager.read(desc, buffer, buffer_size);
        expected = default_file_data;
        got = std::string(buffer, read_bytes);
        assert(expected == got && "Messages mismatch with mixed_order read then write, first read...");
        std::string new_content = "New content longer for testing";
        manager_second.write(desc_2, new_content.data(), new_content.size());
        read_bytes = manager.read(desc, buffer, buffer_size);
        got = std::string(buffer, read_bytes);
        assert(expected == got && "Messages mismatch with mixed_order read then write, second read...");
        manager.close(desc);
        manager_second.close(desc_2);
        std::cout << std::left << std::setw(offset) << "Test mixed_order read then write " << "PASSED\n";

    } catch (std::runtime_error &err) {
        try {
            manager.close(desc);
            manager_second.close(desc_2);
        } catch (std::runtime_error &err) {
            std::cerr << "CRITICAL ERROR: " << err.what() << "\n";
        }
        std::cerr << "CRITICAL ERROR: " << err.what() << "\n";
        assert(false && "An error should not occur!");
    }
}

void TestWriteRead::test_mixed_order_write_then_read() {
    reset_test_file();
    try {
        char buffer[buffer_size];
        desc = manager.open(path_to_existing_file, READ);
        desc_2 = manager_second.open(path_to_existing_file, WRITE);

        std::string new_content = "New content longer for testing";
        manager_second.write(desc_2, new_content.data(), new_content.size());
        read_bytes = manager.read(desc, buffer, buffer_size);
        expected = new_content;
        got = std::string(buffer, read_bytes);
        assert(expected == got && "Messages mismatch with mixed_order write then read...");
        manager.close(desc);
        manager_second.close(desc_2);

        std::cout << std::left << std::setw(offset) << "Test mixed_order write then read " << "PASSED\n";

    } catch (std::runtime_error &err) {
        try {
            manager.close(desc);
            manager_second.close(desc_2);
        } catch (std::runtime_error &err) {
            std::cerr << "CRITICAL ERROR: " << err.what() << "\n";
        }
        std::cerr << "CRITICAL ERROR: " << err.what() << "\n";
        assert(false && "An error should not occur!");
    }
}

void TestWriteRead::test_mixed_order_read_then_write_reader() {
    reset_test_file();
    try {
        char buffer[buffer_size];
        desc = manager.open(path_to_existing_file, READ);
        desc_2 = manager_second.open(path_to_existing_file, READ_WRITE);

        read_bytes = manager.read(desc, buffer, buffer_size);
        expected = default_file_data;
        got = std::string(buffer, read_bytes);
        assert(expected == got && "Messages mismatch with mixed_order read then read_write, first read...");

        read_bytes = manager_second.read(desc_2, buffer, buffer_size);
        got = std::string(buffer, read_bytes);
        assert(expected == got && "Messages mismatch with mixed_order read then read_write, second read...");

        std::string new_content = "New content longer for testing";
        manager_second.write(desc_2, new_content.data(), new_content.size());
        read_bytes = manager.read(desc, buffer, buffer_size);
        got = std::string(buffer, read_bytes);
        assert(expected == got && "Messages mismatch with mixed_order read then read_write, third read...");


        read_bytes = manager_second.read(desc_2, buffer, buffer_size);
        got = std::string(buffer, read_bytes);
        expected = new_content;
        assert(expected == got && "Messages mismatch with mixed_order read then read_write, fourth read...");

        manager.close(desc);
        manager_second.close(desc_2);

        std::cout << std::left << std::setw(offset) << "Test mixed_order read then read_write " << "PASSED\n";

    } catch (std::runtime_error &err) {
        try {
            manager.close(desc);
            manager_second.close(desc_2);
        } catch (std::runtime_error &err) {
            std::cerr << "CRITICAL ERROR: " << err.what() << "\n";
        }
        std::cerr << "CRITICAL ERROR: " << err.what() << "\n";
        assert(false && "An error should not occur!");
    }
}