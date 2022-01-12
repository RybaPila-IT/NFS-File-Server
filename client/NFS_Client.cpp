#include <stdexcept>
#include <iostream>
#include "NFS_Client.h"

NFS_Client::NFS_Client() {
    try {
        socket.connect_to(server_address, port_number);
    } catch (std::runtime_error& err) {
        std::cerr << "main: " << err.what() << "\n";
    }
}

void NFS_Client::open_file(unsigned short open_mode, std::string& path) {
    OpenRequest request(open_mode, path);
    std::string data = request.Serialize();
    std::cout << data;
    handle_session(data);
}

void NFS_Client::handle_session(std::string& data) {
    char buffer[buffer_size];
    try {
        socket.write_data(data.c_str(), data.length() * sizeof (char));

        socket.read_data(buffer, buffer_size);
        std::cout << "Server responded: " << buffer << "\n";
        //TODO - odczekanie na całą wiadomość i konwersja na strigna bo to się wywala
        reply_handler.handle_reply(reinterpret_cast<std::string &>(buffer));

    } catch (std::runtime_error& err) {
        throw std::runtime_error("handle_session: " + std::string(err.what()));
    }
}

void NFS_Client::tmp_func_handle_session_interactive() {
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
