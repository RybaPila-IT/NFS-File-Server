#include <stdexcept>
#include <iostream>
#include <cstring>

#include "NFS_client.h"
#include "reply.h"
#include "request.h"

/* W celu testowania metod serwera - usunąc przed ostatnią wersją */
void NFS_client::tmp_func_handle_session_interactive() {
    std::string end_token = "END", command, response;
    do {
        std::cout << "What do you want to send to the server?\n";
        std::getline(std::cin, command);
        try {
            socket.write_message(command);
            response = socket.read_message();
            std::cout << "Server responded: " << response << "\n";
        } catch (std::runtime_error& err) {
            throw std::runtime_error("handle_session: " + std::string(err.what()));
        }
    } while (command != end_token);
}

NFS_client::NFS_client(const char *server_ip, const int port_number): socket() {
    try {
        socket.connect_to(server_ip, port_number);
    } catch (std::runtime_error& err) {
        std::cerr << "NFS client - constructor: " << err.what() << "\n";
    }
}

void NFS_client::open_file(unsigned short open_mode, std::string& path) {
    OpenRequest request(open_mode, path);
    std::string data = request.serialize();

    std::string reply_data = send_request(data);

    if(is_reply_error_message(reply_data)) {
        ErrorReply error;
        error.deserialize(reply_data);
        throw std::runtime_error("NFS client - open file: error from server: " + error.get_error_message());
    } else {
        OpenReply reply;
        reply.deserialize(reply_data);
    }
    //TODO coś dalej...
}

std::string NFS_client::send_request(std::string& request_data) {
    char buffer[buffer_size];
    try {
        //socket.write_data(request_data.c_str(), request_data.length() * sizeof (char));

        //socket.read_data(buffer, buffer_size);
        std::cout << "Server responded: " << buffer << "\n";
        //TODO - odczekanie na całą wiadomość i konwersja tego co przyjdzie na string
    } catch (std::runtime_error& err) {
        throw std::runtime_error("send_request: " + std::string(err.what()));
    }
    return buffer;
}

bool NFS_client::is_reply_error_message(std::string &reply_data) {
    if(reply_data[0] == 'E')
        return true;
    else
        return false;
}
