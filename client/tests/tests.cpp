#include <iostream>
#include <iomanip>
#include <cassert>

#include "../file_system_manager.h"
#include "tests.h"

#define LOOP_BACK    "127.0.0.1"
#define DEFAULT_PORT 6941

#define CREATE 0
#define READ   1
#define WRITE  2
#define READ_WRITE 3

void test_lseek() {
    FileSystemManager manager;
    std::string path = "test.txt";
    std::string content = "This is sample content which will be saved to test file...";
    std::string expected, got;
    int buffer_size = 10;
    char buffer[buffer_size];
    int desc = -1, read_bytes;

    std::cout << "**************************************************\n";
    std::cout << "************ Starting lseek test suit ************\n";
    std::cout << "**************************************************\n\n";

    try {
        /** Preparation for tests. */
        manager.mount(LOOP_BACK, DEFAULT_PORT);
        desc = manager.open(path, CREATE);
        manager.close(desc);
        desc = manager.open(path, WRITE);
        manager.write(desc, content.data(), content.size());
        manager.close(desc);
        desc = manager.open(path, READ);

        /** Test 0 length lseek. */
        manager.lseek(desc, 0);
        read_bytes = manager.read(desc, buffer, buffer_size);
        expected = "This is sa";
        got = std::string(buffer, read_bytes);
        assert(expected == got && "Messages mismatch with 0 lseek length...");
        std::cout << std::left << std::setw(44) << "Test 0 length lseek" << "PASSED\n";

        /** Test regular lseek. */
        manager.lseek(desc, 10);
        read_bytes = manager.read(desc, buffer, buffer_size);
        expected = "mple conte";
        got = std::string(buffer, read_bytes);
        assert(expected == got && "Messages mismatch with regular lseek length...");
        std::cout << std::left << std::setw(44) << "Test regular length lseek" << "PASSED\n";

        /** Test out-of-range lseek. */
        manager.lseek(desc, 1000);
        read_bytes = manager.read(desc, buffer, buffer_size);
        expected = "";
        got = std::string(buffer, read_bytes);
        assert(expected == got && "Messages mismatch with out-of-range lseek length...");
        std::cout << std::left << std::setw(44) << "Test out-of-range length lseek" << "PASSED\n";

        /** Test negative lseek. */
        manager.lseek(desc, -10);
        read_bytes = manager.read(desc, buffer, buffer_size);
        expected = "st file...";
        got = std::string(buffer, read_bytes);
        assert(expected == got && "Messages mismatch with negative lseek length...");
        std::cout << std::left << std::setw(44) << "Test negative length lseek" << "PASSED\n";

        /** Test negative out-of-range lseek. */
        manager.lseek(desc, -1000);
        read_bytes = manager.read(desc, buffer, buffer_size);
        expected = "This is sa";
        got = std::string(buffer, read_bytes);
        assert(expected == got && "Messages mismatch with negative out-of-range lseek length...");
        std::cout << std::left << std::setw(44) << "Test negative put-of-range length lseek" << "PASSED\n\n";

        /** Clean-up. */
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
    std::cout << "**************************************************\n";
    std::cout << "************ Lseek test suit finished ************\n";
    std::cout << "**************************************************\n";
}
