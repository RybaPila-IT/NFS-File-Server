#include <iostream>
#include "file_system_manager.h"

#define LOOP_BACK    "127.0.0.1"
#define DEFAULT_PORT 6941

#define CREATE 1
#define READ   2
#define WRITE  3


int main() {
    FileSystemManager manager;
    std::string path = "test.txt";
    try {
        auto desc = manager.open(CREATE, path);
        std::cout << "File opened as expected! Descriptor is: " << desc << "\n";
        manager.close(desc);
        std::cout << "File closed successfully!\n";
        manager.close(desc);
        std::cout << "This line should not be printed...\n";
    } catch (std::runtime_error& err) {
        std::cout << "Error regarding closing closed file: " << err.what() << "\n";
    }
    return 0;
}