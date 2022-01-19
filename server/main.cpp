#include <stdexcept>
#include <iostream>
#include <thread>

#include "socket.h"
#include "request_handler.h"

#define DEFAULT_PORT  6941
#define BACKLOG_QUEUE 30
#define LOOP_BACK     "127.0.0.1"

void handle_session(int socket_fd) {
    TcpSocket session_socket(socket_fd);
    RequestHandler request_manager(socket_fd);
    std::string message;
    std::cout << "Staring new session...\n";
    do {
        try {
            message = session_socket.read_message();
            if (!message.empty()) {
                request_manager.handle_request(message);
            }
        } catch (std::runtime_error &err) {
            throw std::runtime_error("server main - handle_session: " + std::string(err.what()));
        }
    } while (!message.empty());
    session_socket.close_socket();
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

int main() {
    TcpSocket tcp_socket;
    try {
        tcp_socket = TcpSocket(LOOP_BACK, DEFAULT_PORT);
        tcp_socket.switch_to_listen_mode(BACKLOG_QUEUE);
    } catch (std::runtime_error &err) {
        std::cerr << "main: " << err.what() << "\n";
        return -1;
    }
    std::cout << "Address: " << LOOP_BACK << "; Port: " << DEFAULT_PORT << ";\n";
    std::cout << "Server begins listening...\n";

    try {
        handle_incoming_connections(tcp_socket);
    } catch (std::runtime_error &err) {
        std::cerr << "main: " << err.what() << "\n";
        return -1;
    }
    return 0;
}