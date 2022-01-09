#include <stdexcept>
#include <iostream>
#include <thread>
#include "socket.h"
#include "../Message/test.h"

#define DEFAULT_PORT  6941
#define BACKLOG_QUEUE 30
#define LOOP_BACK     "127.0.0.1"

void handle_session(int socket_fd) {
    TcpSocket session_socket(socket_fd);
    int buffer_size = 1024;
    char buffer[buffer_size];
    std::string ack_token = "ACK";
    bool finished;
    ReadReply rRep = ReadReply("AlaMaKota");
    ReadRequest rReq = ReadRequest(0);

    std::cout << "Staring new session...\n";
    do {
        try {
            finished = session_socket.read_data(buffer, buffer_size);


        } catch (std::runtime_error &err) {
            throw std::runtime_error("handle_session: reading from socket " + std::string(err.what()));
        }
        if (!finished) {
            std::cout << "Received: " << buffer << "\n";
            try {
                rReq.Deserialize(buffer);
                std::cout << "REC RQ: " << rReq.info.requestType << "|REC RQ SIZE: "<<rReq.info.dataSize <<"|REC RQ FD: "<<rReq.fileDescriptor <<"\n";
                //session_socket.write_data(ack_token.c_str(), ack_token.length() * sizeof(char));
                std::string reply = rRep.Serialize();
                session_socket.write_data(reply.c_str(), reply.length() * sizeof (char));
            } catch (std::runtime_error &err) {
                throw std::runtime_error("handle_session: write response error: " + std::string(err.what()));
            }
        }
    } while (!finished);
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