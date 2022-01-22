#include <iostream>
#include "file_system_manager.h"

#define LOOP_BACK    "127.0.0.1"
#define DEFAULT_PORT 6941

#define CREATE 0
#define READ   1
#define WRITE  2
#define READ_WRITE 3

int main() {
    FileSystemManager manager;
    std::string path = "test.txt";
    try {
        manager.mount(LOOP_BACK, DEFAULT_PORT);
        auto desc = manager.open(path, READ);
        std::cout << "File opened as expected! Descriptor is: " << desc << "\n";
        manager.close(desc);
        std::cout << "File closed successfully!\n";
        desc = manager.open(path, READ);
        std::cout << "File opened as expected! Descriptor is: " << desc << "\n";
        manager.close(desc);
    } catch (std::runtime_error& err) {
        std::cout << "Unexpected error: " << err.what() << "\n";
    }
    return 0;
}