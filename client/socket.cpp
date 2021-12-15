#include <stdexcept>
#include <cstring>
#include "socket.h"

#define ERRNO std::string(strerror(errno))

void TcpSocket::init_socket() {
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd == ERROR_CODE)
        throw std::runtime_error("init_socket: create socket error; errno value: " + ERRNO);
}

void TcpSocket::init_socket_address(const std::string &ip_address, int port_number) {
    struct hostent* hp;
    socket_address.sin_family = AF_INET;
    socket_address.sin_port = htons(port_number);
    hp = gethostbyname(ip_address.c_str());
    if (!hp) {
        throw std::runtime_error("init_socket_address: gethostbyname error; errno value: " + ERRNO);
    }
    std::memcpy((char *) &socket_address.sin_addr, (char *) hp->h_addr,hp->h_length);
}

void TcpSocket::bind_socket_to_address() {
    if (bind(sock_fd, (struct sockaddr*)&socket_address, sizeof (socket_address)) == ERROR_CODE)
        throw std::runtime_error("bind_socket_to_address: bind error; errno value: " + ERRNO);
}

TcpSocket::TcpSocket(const std::string& socket_ip_address, int port_number): sock_fd(0), socket_address({}) {
    try {
        init_socket();
        init_socket_address(socket_ip_address, port_number);
        bind_socket_to_address();
    } catch (std::runtime_error& err) {
        throw std::runtime_error("TcpSocket: " + std::string(err.what()));
    }
}

TcpSocket::TcpSocket(): sock_fd(0), socket_address({}) {}

TcpSocket::TcpSocket(const TcpSocket& socket): sock_fd(socket.sock_fd), socket_address(socket.socket_address) {}

TcpSocket::~TcpSocket() {
    if (sock_fd > 0)
        close(sock_fd);
}

TcpSocket &TcpSocket::operator=(const TcpSocket &socket)  {
    throw std::runtime_error("TcpSocket: assignment operator is banned!");
}

TcpSocket &TcpSocket::operator=(TcpSocket &&socket) noexcept {
    if (this != &socket) {
        if (sock_fd > 0)
            close(sock_fd);
        sock_fd = std::move(socket.sock_fd);
        socket_address = std::move(socket.socket_address);
        socket.sock_fd = ERROR_CODE;
    }
    return *this;
}

address TcpSocket::get_address() const {
    return socket_address;
}

void TcpSocket::switch_to_listen_mode(int backlog) {
    listen(sock_fd, backlog);
}

void TcpSocket::connect_to(const std::string& socket_ip_address, int port_number) {
    if (sock_fd != 0)
        throw std::runtime_error("connect_to: error, socket is already in use!");
    try {
        init_socket();
        init_socket_address(socket_ip_address, port_number);
    } catch (std::runtime_error& err) {
        throw std::runtime_error("connect_to: initializing socket data " + std::string(err.what()));
    }
    if (connect(sock_fd, (struct sockaddr *) &socket_address, sizeof socket_address)== ERROR_CODE)
        throw std::runtime_error("connect_to: connect error; errno value: " + ERRNO);
}

TcpSocket TcpSocket::accept_connection() {
    auto new_socket = TcpSocket();
    new_socket.sock_fd = accept(sock_fd, (struct sockaddr*) nullptr, (socklen_t*) nullptr);
    if (new_socket.sock_fd == ERROR_CODE)
        throw std::runtime_error("accept_connection: accept error; errno value: " + ERRNO);
    return new_socket;
}

bool TcpSocket::read_data(char *buffer, int buffer_size) {
    memset(buffer, 0, buffer_size * sizeof (char));
    auto r_val = read(sock_fd ,buffer, buffer_size);
    if (r_val == -1)
        throw std::runtime_error("read_data: read error; errno value: " + ERRNO);
    return r_val == 0;
}

void TcpSocket::write_data(const char *buffer, int buffer_size) {
    if (write(sock_fd, buffer, buffer_size * sizeof(char) ) == ERROR_CODE)
        throw std::runtime_error("write_data: write error; errno value: " + ERRNO);
}
