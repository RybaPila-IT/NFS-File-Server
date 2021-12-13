#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <stdexcept>
#include <unistd.h>
#include <iostream>

#define DEFAULT_PORT htons(6941)
#define ERRNO std::string(strerror(errno))

const int ERROR_CODE = -1;
const int BACKLOG_QUEUE = 30;
const int BUFFER_SIZE = 1024;

int init_socket() {
    auto socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == ERROR_CODE)
        throw std::runtime_error("init_socket: create socket error; errno value: " + ERRNO);
    return socket_desc;
}

struct sockaddr_in init_socket_address() {
    struct sockaddr_in sock_address {};
    sock_address.sin_family = AF_INET;
    sock_address.sin_addr.s_addr = INADDR_ANY;
    sock_address.sin_port = DEFAULT_PORT;
    return sock_address;
}

void bind_socket_to_address(int sock_fd, struct sockaddr_in& socket_address) {
    if (bind(sock_fd, (struct sockaddr*)&socket_address, sizeof (socket_address)) == ERROR_CODE) {
        throw std::runtime_error("bind_socket_to_address: bind error; errno value: " + ERRNO);
    }
}

void switch_socket_to_listen_mode(int sock_fd) {
    listen(sock_fd, BACKLOG_QUEUE);
}

int init_tcp_server_socket() {
    int sock_fd;
    struct sockaddr_in sock_address {};
    try {
        sock_fd = init_socket();
        sock_address = init_socket_address();
        bind_socket_to_address(sock_fd, sock_address);
        switch_socket_to_listen_mode(sock_fd);
    } catch (std::runtime_error& err) {
        throw std::runtime_error("init_tcp_server_socket: " + std::string(err.what()));
    }
    return sock_fd;
}

void handle_incoming_connections(int sock_fd) {
    ssize_t r_val;
    char buffer[BUFFER_SIZE];
    do {
        auto msg_sock_fd = accept(sock_fd,(struct sockaddr *) nullptr,(socklen_t *) nullptr);
        if (msg_sock_fd == -1 )
            throw std::runtime_error("handle_incoming_connections: accept error; errno value: " + ERRNO);
        else do {
                memset(buffer, 0, sizeof (buffer));
                r_val = read(msg_sock_fd ,buffer, BUFFER_SIZE);
                if (r_val == -1) {
                    close(msg_sock_fd);
                    throw std::runtime_error("handle_incoming_connections: read error; errno value: " + ERRNO);
                }
                if (r_val == 0)
                    std::cout << "Ending connection...\n";
                else
                    std::cout << "Read: " << buffer << "\n";
            } while (r_val > 0);
        close(msg_sock_fd);
    } while(true);
}

int main() {
    int sock_fd;
    try {
        sock_fd = init_tcp_server_socket();
    } catch (std::runtime_error& err) {
        std::cerr << "main: " << err.what() << "\n";
        return -1;
    }
    std::cout << "Server begins listening...\n";
    try {
        handle_incoming_connections(sock_fd);
    } catch (std::runtime_error& err) {
        std::cerr << "main: " << err.what() << "\n";
        return -1;
    }
    return 0;
}