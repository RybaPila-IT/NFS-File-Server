#include <iostream>
#include <string>
#include "socket.h"

#define LOOP_BACK    "127.0.0.1"
#define DEFAULT_PORT 6941


void handle_session(TcpSocket& socket) {
    int buffer_size = 1024;
    char buffer[buffer_size];
    std::string end_token = "END", command;
    do {
        std::cout << "What do you want to send to server?\n";
        std::cin >> command;
        try {
            socket.write_data(command.c_str(), command.length() * sizeof (char));
            socket.read_data(buffer, buffer_size);
            std::cout << "Server responded: " << buffer << "\n";
        } catch (std::runtime_error& err) {
            throw std::runtime_error("handle_session: " + std::string(err.what()));
        }
    } while (command != end_token);
}

int main() {
    std::string data = "Half a league, half a league . . .";
    TcpSocket socket;
    try {
        socket.connect_to(LOOP_BACK, DEFAULT_PORT);
        handle_session(socket);
    } catch (std::runtime_error& err) {
        std::cerr << "main: " << err.what() << "\n";
        return -1;
    }
    return 0;
}

