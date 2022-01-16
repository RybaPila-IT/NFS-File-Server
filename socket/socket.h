#ifndef _SOCKET_H_
#define _SOCKET_H_

#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string>
#include <vector>

using address = struct sockaddr_in;

class TcpSocket {
private:
    static const int ERROR_CODE = -1;
    static const int BUFFER_SIZE = 1024;

    std::vector<char> buffer;
    int sock_fd;
    address socket_address;

    void init_socket();
    void init_socket_address(const std::string& ip_address, int port_number);
    void bind_socket_to_address();

    std::string obtain_message(int read_bytes);

public:
    TcpSocket();
    TcpSocket(const TcpSocket& socket) = delete;
    TcpSocket(TcpSocket&& socket);
    TcpSocket(int soc_fd);
    TcpSocket(const std::string& socket_ip_address, int port_number);
    ~TcpSocket();

    TcpSocket& operator=(TcpSocket&& socket) noexcept;
    TcpSocket& operator=(const TcpSocket& socket) = delete;

    address get_address() const;

    int accept_connection();
    void switch_to_listen_mode(int backlog);
    void connect_to(const std::string& socket_ip_address, int port_number);

    std::string read_message();
    void write_message(std::string& message);
};

#endif //_SOCKET_H_
