#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <cstring>
#include <stdexcept>
#include <iostream>

#define DEFAULT_PORT 6941
#define LOOP_BACK    "127.0.0.1"
#define ERRNO        std::string(strerror(errno))

const int ERROR_CODE = -1;
const int BACKLOG_QUEUE = 30;
const int BUFFER_SIZE = 1024;

int init_socket() {
    auto socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == ERROR_CODE)
        throw std::runtime_error("init_socket: create socket error; errno value: " + ERRNO);
    return socket_desc;
}

struct sockaddr_in init_server_address(const std::string& server_ip_address, const int server_port) {
    struct sockaddr_in server_address {};
    struct hostent* hp;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(server_port);
    hp = gethostbyname(server_ip_address.c_str());
    if (!hp) {
        throw std::runtime_error("init_server_address: gethostbyname error; errno value: " + ERRNO);
    }
    std::memcpy((char *) &server_address.sin_addr, (char *) hp->h_addr,hp->h_length);
    return server_address;
}

void bind_socket_to_address(int sock_fd, struct sockaddr_in& socket_address) {
    if (bind(sock_fd, (struct sockaddr*)&socket_address, sizeof (socket_address)) == ERROR_CODE) {
        throw std::runtime_error("bind_socket_to_address: bind error; errno value: " + ERRNO);
    }
}

void switch_socket_to_listen_mode(int sock_fd) {
    listen(sock_fd, BACKLOG_QUEUE);
}

int init_tcp_server_socket(const std::string& server_ip_address, const int server_port) {
    int sock_fd;
    struct sockaddr_in sock_address {};
    try {
        sock_fd = init_socket();
        sock_address = init_server_address(server_ip_address, server_port);
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
        sock_fd = init_tcp_server_socket(LOOP_BACK, DEFAULT_PORT);
    } catch (std::runtime_error& err) {
        std::cerr << "main: " << err.what() << "\n";
        return -1;
    }
    std::cout << "Address: " << LOOP_BACK << "; Port: " << DEFAULT_PORT << ";\n";
    std::cout << "Server begins listening...\n";
    try {
        handle_incoming_connections(sock_fd);
    } catch (std::runtime_error& err) {
        std::cerr << "main: " << err.what() << "\n";
        return -1;
    }
    return 0;
}