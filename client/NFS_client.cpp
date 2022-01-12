#include <stdexcept>
#include <iostream>

#include "NFS_client.h"
#include "Reply.h"
#include "Request.h"

NFS_client::NFS_client(std::string &server_ip, int port_number): port_number(port_number), server_address(server_ip) {
    try {
        socket.connect_to(server_address, port_number);
    } catch (std::runtime_error& err) {
        std::cerr << "NFS client - constructor: " << err.what() << "\n";
    }
}

void NFS_client::open_file(unsigned short open_mode, std::string& path) {
    OpenRequest request(open_mode, path);
    std::string data = request.Serialize();

    std::string reply_data = send_request(data);

    if(is_reply_error_message(reply_data)) {
        ErrorReply error(""); //TODO wyrzucić wartość krzak jak będzie konstruktor domyślny
        error.Deserialize(reply_data);
        throw std::runtime_error("NFS client - open file: error from server: " + error.errorMsg);
    } else {
        OpenReply reply(1234); //TODO na razie wartość krzak dopóki nie będzie domyślnego konstruktora
        reply.Deserialize(reply_data);
    }
    //TODO coś dalej...
}

std::string NFS_client::send_request(std::string& request_data) {
    char buffer[buffer_size];
    try {
        socket.write_data(request_data.c_str(), request_data.length() * sizeof (char));

        socket.read_data(buffer, buffer_size);
        std::cout << "Server responded: " << buffer << "\n";
        //TODO - odczekanie na całą wiadomość i konwersja tego co przyjdzie na string
    } catch (std::runtime_error& err) {
        throw std::runtime_error("send_request: " + std::string(err.what()));
    }
    return buffer;
}

void NFS_client::tmp_func_handle_session_interactive() {
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
            throw std::runtime_error("send_request: " + std::string(err.what()));
        }
    } while (command != end_token);
}

bool NFS_client::is_reply_error_message(std::string &reply_data) {
    //TODO jaki format będzie po otrzymaniu danych z metody send_request
    return false;
}
