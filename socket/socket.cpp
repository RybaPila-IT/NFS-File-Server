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

TcpSocket::TcpSocket(const std::string& socket_ip_address, int port_number): sock_fd(0), socket_address({}),
    buffer(std::vector<char>(BUFFER_SIZE)) {
    try {
        init_socket();
        init_socket_address(socket_ip_address, port_number);
        bind_socket_to_address();
    } catch (std::runtime_error& err) {
        throw std::runtime_error("TcpSocket: " + std::string(err.what()));
    }
}

TcpSocket::TcpSocket(): sock_fd(0), socket_address({}), buffer(std::vector<char>(BUFFER_SIZE)) {}
TcpSocket::TcpSocket(int soc_fd): sock_fd(soc_fd), socket_address({}), buffer(std::vector<char>(BUFFER_SIZE)) {}
TcpSocket::TcpSocket(TcpSocket&& socket): sock_fd(std::move(socket.sock_fd)), socket_address(std::move(socket.socket_address)),
    buffer(std::move(socket.buffer)){
    socket.sock_fd = ERROR_CODE;
}

TcpSocket::~TcpSocket() {
    if (sock_fd > 0)
        close(sock_fd);
}

TcpSocket &TcpSocket::operator=(TcpSocket &&socket) noexcept {
    if (this != &socket) {
        if (sock_fd > 0)
            close(sock_fd);
        sock_fd = std::move(socket.sock_fd);
        socket_address = std::move(socket.socket_address);
        buffer = std::move(socket.buffer);
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

int TcpSocket::accept_connection() {
    int new_sock_fd = accept(sock_fd, (struct sockaddr*) nullptr, (socklen_t*) nullptr);
    if (new_sock_fd == ERROR_CODE)
        throw std::runtime_error("accept_connection: accept error; errno value: " + ERRNO);
    return new_sock_fd;
}

std::string TcpSocket::read_message() {
    int read_bytes;
    std::string message_bytes;
    read_bytes = read(sock_fd, buffer.data(), buffer.size());
    if (read_bytes == -1)
        throw std::runtime_error("read_message: read error; errno value: " + ERRNO);
    if (read_bytes > 0) {
        if (read_bytes < 4)
            throw std::runtime_error("read_message: unable to determine size of the message; read bytes: " + std::to_string(read_bytes));
        try {
            message_bytes = obtain_message(read_bytes);
        } catch (std::runtime_error& err) {
            throw std::runtime_error("read_message: " + std::string(err.what()));
        }
    }
    return message_bytes;
}

std::string TcpSocket::obtain_message(int read_bytes) {
    int left_message_data_size, obtained_data_size;
    int buffer_offset = 4;
    std::string message;

    left_message_data_size = (int) ((unsigned char)(buffer[0]) << 24 |
                                    (unsigned char)(buffer[1]) << 16 |
                                    (unsigned char)(buffer[2]) << 8 |
                                    (unsigned char)(buffer[3]));
    if (left_message_data_size == 0)
        throw std::runtime_error("obtain_message: message is empty.");

    while (left_message_data_size) {
        obtained_data_size = std::min(left_message_data_size, read_bytes - buffer_offset);
        message += std::string(buffer.data() + buffer_offset, obtained_data_size);
        left_message_data_size -= obtained_data_size;
        if (left_message_data_size) {
            buffer_offset = 0;
            read_bytes = read(sock_fd, buffer.data(), buffer.size());
            if (read_bytes == ERROR_CODE)
                throw std::runtime_error("obtain_message: error while reading from socket.");
            if (read_bytes == 0)
                throw std::runtime_error("obtain_message: client closed the connection.");
        }
    }

    return message;
}

void TcpSocket::write_message(std::string& message) {
    int left_message_size = message.length();
    int buffer_offset = 4;
    int message_offset = 0;
    int copied_bytes, whole_message_size;

    buffer[3] =  left_message_size & 0x000000ff;
    buffer[2] = (left_message_size & 0x0000ff00) >> 8;
    buffer[1] = (left_message_size & 0x00ff0000) >> 16;
    buffer[0] = (left_message_size & 0xff000000) >> 24;

    while (left_message_size > 0) {
        copied_bytes = std::min(left_message_size, BUFFER_SIZE - buffer_offset);
        whole_message_size = copied_bytes + buffer_offset;
        memcpy(buffer.data() + buffer_offset,message.data() + message_offset,copied_bytes);
        message_offset += copied_bytes;
        left_message_size -= copied_bytes;
        if (write(sock_fd, buffer.data(), whole_message_size * sizeof(char) ) != whole_message_size * sizeof(char))
            throw std::runtime_error("write_message: write error; errno value: " + ERRNO);
        buffer_offset = 0;
    }
}

void TcpSocket::close_socket() {
    if (sock_fd > 0)
        close(sock_fd);
}
