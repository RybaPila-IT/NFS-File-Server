#include "test_lseek.h"
#include "test_open_close.h"

#define SERVER_IP "127.0.0.1"
#define PORT 6941

void test_lseek() {
    TestLseek test_lseek(SERVER_IP, PORT);
    test_lseek.run_all_tests();
}

void test_open_close() {
    TestOpenClose test_open_close(SERVER_IP, PORT);
    test_open_close.run_all_tests();
}


int main() {
    test_lseek();
    test_open_close();
    return 0;
}