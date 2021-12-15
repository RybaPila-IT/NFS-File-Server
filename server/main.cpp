#include <sys/socket.h>
#include <netinet/in.h>
#include <stdexcept>
#include <iostream>
#include "socket.h"

#define DEFAULT_PORT  6941
#define BACKLOG_QUEUE 30
#define LOOP_BACK     "127.0.0.1"

const int BUFFER_SIZE = 1024;

void handle_incoming_connections(TcpSocket& socket) {
    char buffer[BUFFER_SIZE];
    do {
        TcpSocket new_socket;
        try {
            new_socket = socket.accept_connection();
        } catch (std::runtime_error& err) {
            throw std::runtime_error("handle_incoming_connections: accepting connection " + std::string(err.what()));
        }
        bool finished;
        do {
            try {
                finished = new_socket.read_data(buffer, BUFFER_SIZE);
            } catch (std::runtime_error& err) {
                throw std::runtime_error("handle_incoming_connection: reading from socket " + std::string(err.what()));
            }
            if (finished)
                std::cout << "Ending connection...\n";
            else
                std::cout << "Received: " << buffer << "\n";
            } while (!finished);
    } while(true);
}

int main() {
    TcpSocket tcp_socket;
    try {
        tcp_socket = TcpSocket(LOOP_BACK, DEFAULT_PORT);
        tcp_socket.switch_to_listen_mode(BACKLOG_QUEUE);
    } catch (std::runtime_error& err) {
        std::cerr << "main: " << err.what() << "\n";
        return -1;
    }
    std::cout << "Address: " << LOOP_BACK << "; Port: " << DEFAULT_PORT << ";\n";
    std::cout << "Server begins listening...\n";
    try {
        handle_incoming_connections(tcp_socket);
    } catch (std::runtime_error& err) {
        std::cerr << "main: " << err.what() << "\n";
        return -1;
    }
    return 0;
}