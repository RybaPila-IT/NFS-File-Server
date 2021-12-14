#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <cstring>
#include <unistd.h>
#include <iostream>
#include <string>

#define DATA         "Half a league, half a league . . ."
#define LOOP_BACK    "127.0.0.1"
#define DEFAULT_PORT 6941
#define ERRNO        std::string(strerror(errno))

const int ERROR_CODE = -1;

int init_tcp_socket() {
    auto sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd == ERROR_CODE) {
        throw std::runtime_error("init_socket: create socket; errno value: " + ERRNO);
    }
    return sock_fd;
}

struct sockaddr_in init_server_address(const std::string& server_ip_address, const int port_number) {
    struct sockaddr_in socket_address {};
    struct hostent* hp;
    socket_address.sin_family = AF_INET;
    socket_address.sin_port = htons(port_number);
    hp = gethostbyname(server_ip_address.c_str());
    if (!hp) {
        throw std::runtime_error("init_server_address: gethostbyname error; errno value: " + ERRNO);
    }
    std::memcpy((char *) &socket_address.sin_addr, (char *) hp->h_addr,hp->h_length);
    return socket_address;
}

void connect_to_server(int socket_fd, struct sockaddr_in& server_address) {
    if (connect(socket_fd, (struct sockaddr *) &server_address, sizeof server_address)== -1) {
        throw std::runtime_error("connect_to_server: connect error; errno value: " + ERRNO);
    }
}

int establish_connection(const std::string& server_ip_address, const int server_port_number) {
    int sock_fd;
    struct sockaddr_in server_address;
    try {
        sock_fd = init_tcp_socket();
        server_address = init_server_address(server_ip_address, server_port_number);
        connect_to_server(sock_fd, server_address);
    } catch (std::runtime_error& err) {
        throw std::runtime_error("establish_connection: " + std::string(err.what()));
    }
    return sock_fd;
}

int main() {
    int sock_fd;
    try {
        sock_fd = establish_connection(LOOP_BACK, DEFAULT_PORT);
    } catch (std::runtime_error& err) {
        std::cerr << "main: " << err.what() << "\n";
        return ERROR_CODE;
    }
    if (write(sock_fd, DATA, sizeof DATA) == -1)
        std::cerr << "Error when writing on stream socket" << std::endl;

    close(sock_fd);
    return 0;
}

