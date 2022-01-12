#include <stdexcept>
#include <iostream>
#include <thread>

#include "socket.h"
#include "request_handler.h"


#define DEFAULT_PORT  6941
#define BACKLOG_QUEUE 30
#define LOOP_BACK     "127.0.0.1"

std::string read_missing_message_part(TcpSocket& socket, char* buffer, int buffer_size, int left_message_data_size) {
    int read_bytes;
    std::string message_bytes;

    do {
        try {
            read_bytes = socket.read_data(buffer, buffer_size);
        } catch (std::runtime_error &err) {
            throw std::runtime_error("read_missing_message_part: reading from socket: " + std::string(err.what()));
        }
        if (read_bytes == 0)
            throw std::runtime_error("read_missing_message_part: client closed the connection");

        message_bytes += std::string(buffer, std::min(left_message_data_size, read_bytes));
        left_message_data_size -= std::min(left_message_data_size, read_bytes);

    } while (left_message_data_size);

    return message_bytes;
}

std::string read_message(TcpSocket& socket, char* buffer, int buffer_size, int read_bytes) {
    std::string message_bytes;
    int left_message_data_size;

    if (read_bytes < 4)
        throw std::runtime_error("read_message: unable to determine size of the message; read bytes: " + std::to_string(read_bytes));

    left_message_data_size = (int) ((unsigned char)(buffer[0]) << 24 |
                                    (unsigned char)(buffer[1]) << 16 |
                                    (unsigned char)(buffer[2]) << 8 |
                                    (unsigned char)(buffer[3]));
    if (left_message_data_size == 0)
        throw std::runtime_error("read_message: message is corrupted");

    // - and + 4 is caused due to offset of initial int making up the message length.
    message_bytes = std::string(buffer + 4, std::min(left_message_data_size, read_bytes - 4));
    left_message_data_size -= std::min(left_message_data_size, read_bytes - 4);

    if (left_message_data_size > 0) {
        try {
            message_bytes += read_missing_message_part(socket, buffer, buffer_size, left_message_data_size);
        } catch (std::runtime_error& err) {
            throw std::runtime_error("read_message: " + std::string(err.what()));
        }
    }

    return message_bytes;
}


void handle_session(int socket_fd) {
    TcpSocket session_socket(socket_fd);
    // Size is set to be tiny for testing purposes.
    // Feel free to change it (or event SHOULD) to something reasonable.
    int buffer_size = 8;
    char buffer[buffer_size];
    std::string ack_token = "ACK";
    std::string message_bytes;
    int read_bytes;

    std::cout << "Staring new session...\n";
    do {
        try {
             read_bytes = session_socket.read_data(buffer, buffer_size);
        } catch (std::runtime_error &err) {
            throw std::runtime_error("handle_session: reading from socket " + std::string(err.what()));
        }
        if (read_bytes != 0) {
            try {
                message_bytes = read_message(session_socket, buffer, buffer_size, read_bytes);
            } catch (std::runtime_error& err) {
                throw std::runtime_error("handle_session: " + std::string(err.what()));
            }
            /*
             * Here is the part where the whole message is being read from the socket.
             *
             * The message sent from client is present under message_bytes variable.
             * It contains bytes stored in std::string form, which has been sent from the client.
             */
            std::cout << "Received: " << message_bytes << "\n";
            request_handler handler(socket_fd);
            handler.handle_request(message_bytes);
            try {
                session_socket.write_data(ack_token.data(), ack_token.length() * sizeof(char));
            } catch (std::runtime_error &err) {
                throw std::runtime_error("handle_session: write response error: " + std::string(err.what()));
            }
        }
    } while (read_bytes != 0);
    std::cout << "Ending session...\n";
}

void handle_incoming_connections(TcpSocket& socket) {
    do {
        try {
            std::thread t1(handle_session, socket.accept_connection());
            t1.detach();
        } catch (std::runtime_error& err) {
            throw std::runtime_error("handle_incoming_connections: session management " + std::string(err.what()));
        }
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