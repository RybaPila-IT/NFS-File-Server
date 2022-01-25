#include "tests.h"
#include "test_open_close.h"

#define SERVER_IP "127.0.0.1"
#define PORT 6941

int main() {
    test_lseek(SERVER_IP, PORT);
    TestOpenClose test_open_close(SERVER_IP, PORT);
    test_open_close.run_all_tests();
    return 0;
}