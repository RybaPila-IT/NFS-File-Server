#include "test_lseek.h"
#include "test_open_close.h"
#include "test_read_and_write.h"

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

void test_write_read() {
    TestWriteRead test_write_read(SERVER_IP, PORT);
    test_write_read.run_all_tests();

}


int main() {
    test_lseek();
    test_open_close();
    test_write_read();
    return 0;
}