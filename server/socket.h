#ifndef SERVER_SOCKET_H
#define SERVER_SOCKET_H

using address = struct sockaddr_in;

class TcpSocket {
private:
    static const int ERROR_CODE = -1;

    int sock_fd;
    address socket_address;

    void init_socket();
    void init_socket_address(const std::string& ip_address, int port_number);
    void bind_socket_to_address();

public:
    TcpSocket();
    TcpSocket(const TcpSocket& socket);
    TcpSocket(const std::string& socket_ip_address, int port_number);
    ~TcpSocket();

    TcpSocket& operator=(TcpSocket&& socket) noexcept;
    TcpSocket& operator=(const TcpSocket& socket);

    address get_address() const;
    void switch_to_listen_mode(int backlog);
    TcpSocket accept_connection();
    bool read_data(char* buffer, int buffer_size);
};

#endif //SERVER_SOCKET_H
