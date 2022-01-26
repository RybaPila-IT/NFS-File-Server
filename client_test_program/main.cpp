#include "test_lseek.h"
#include "test_open_close.h"
#include "test_read_and_write.h"
#include "test_fstat.h"

#define LOOP_BACK "127.0.0.1"
#define DEFAULT_PORT 6941

void test_lseek(const char* ip_address, int port_number) {
    TestLseek test_lseek(ip_address, port_number);
    test_lseek.run_all_tests();
}

void test_open_close(const char* ip_address, int port_number) {
    TestOpenClose test_open_close(ip_address, port_number);
    test_open_close.run_all_tests();
}

void test_write_read(const char* ip_address, int port_number) {
    TestWriteRead test_write_read(ip_address, port_number);
    test_write_read.run_all_tests();
}

void test_fstat(const char* ip_address, int port_number) {
    TestFstat test_fstat(ip_address, port_number);
    test_fstat.run_all_tests();
}


int main(int argc, char* argv[]) {
    const char* ip_address = (argc == 3 ? argv[1] : LOOP_BACK);
    int port_number = (argc == 3 ? std::stoi(argv[2]) : DEFAULT_PORT);
    /* Start of test section. */
    test_lseek(ip_address, port_number);
    test_open_close(ip_address, port_number);
    test_write_read(ip_address, port_number);
    test_fstat(ip_address, port_number);
    /* End of test section. */
    return 0;
}