#include <stdexcept>
#include <iostream>
#include <thread>

#include "socket.h"
#include "request_handler.h"

#define DEFAULT_PORT  6941
#define BACKLOG_QUEUE 30
#define LOOP_BACK     "127.0.0.1"

void handle_session(int socket_fd) {
    std::cout << "Staring new session...\n";
    RequestHandler request_manager(socket_fd);
    try {
        request_manager.handle_incoming_requests();
    } catch (std::runtime_error& err) {
        std::cerr << "Abnormal session termination due to an error: " << err.what() << "\n";
    }
    std::cout << "Ending session...\n";
}

void handle_incoming_connections(TcpSocket &socket) {
    do {
        try {
            std::thread t1(handle_session, socket.accept_connection());
            t1.detach();
        } catch (std::runtime_error &err) {
            throw std::runtime_error("handle_incoming_connections: session management " + std::string(err.what()));
        }
    } while (true);
}

int main(int argc, char *argv[]) {
    std::string ip_address = (argc == 3 ? argv[1] : LOOP_BACK);;
    int port_number = (argc == 3 ? std::stoi(argv[2]) : DEFAULT_PORT);
    TcpSocket tcp_socket;
    try {
        tcp_socket = TcpSocket(ip_address, port_number);
        tcp_socket.switch_to_listen_mode(BACKLOG_QUEUE);
    } catch (std::runtime_error &err) {
        std::cerr << "main: " << err.what() << "\n";
        return -1;
    }
    std::cout << "Address: " << ip_address << "; Port: " << port_number << ";\n";
    std::cout << "Server begins listening...\n";

    try {
        handle_incoming_connections(tcp_socket);
    } catch (std::runtime_error &err) {
        std::cerr << "main: " << err.what() << "\n";
        return -1;
    }
    return 0;
}