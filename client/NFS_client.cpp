#include <stdexcept>
#include <iostream>
#include <cstring>

#include "NFS_client.h"
#include "reply.h"
#include "request.h"

/* W celu testowania metod serwera - usunąc przed ostatnią wersją */
void NFS_client::tmp_func_handle_session_interactive() {
    int bytes_amount;
    char buffer[buffer_size];
    std::string end_token = "END", command;
    do {
        std::cout << "How many bytes will be sent to server?\n";
        std::cin >> bytes_amount;
        // This loop is used in order to ensure lack of the buffer overflow
        // while performing the memcpy function later on.
        while (bytes_amount >= 1020) {
            std::cout << "Message is to large... Please provide less bytes!\n";
            std::cin >> bytes_amount;
        }
        // Since cin leaves the '\n' token and overall mess,
        // we use cin ignore to get fresh start for reading user input with get_line().
        std::cin.ignore(1000000, '\n');
        std::cout << "What do you want to send to the server?\n";
        std::getline(std::cin, command);
        // Resize in order to make it easier for user to test sending.
        // No need to count bytes by hand while typing :) .
        command.resize(bytes_amount, '?');

        // Encoding the bytes amount by bytes 'and' and 'shift'.
        // Should be moved to BytesEncoder later.
        buffer[3] =  bytes_amount & 0x000000ff;
        buffer[2] = (bytes_amount & 0x0000ff00) >> 8;
        buffer[1] = (bytes_amount & 0x00ff0000) >> 16;
        buffer[0] = (bytes_amount & 0xff000000) >> 24;
        // Appending the command data after the bytes part.
        std::memcpy(buffer + 4, command.data(), command.length() * sizeof (char ));

        try {
            socket.write_data(buffer, command.length() * sizeof (char) + 4);
            //std::cout << "DATA WRITTEN\n";
            socket.read_data(buffer, buffer_size);
            std::cout << "Server responded: " << buffer << "\n";
        } catch (std::runtime_error& err) {
            throw std::runtime_error("handle_session: " + std::string(err.what()));
        }
    } while (command != end_token);
}

NFS_client::NFS_client(const char *server_ip, const int port_number) {
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
        ErrorReply error(""); //TODO wyrzucić wartość krzak jak będzie konstruktor domyślny
        error.deserialize(reply_data);
        throw std::runtime_error("NFS client - open file: error from server: " + error.get_error_message());
    } else {
        OpenReply reply; //TODO na razie wartość krzak dopóki nie będzie domyślnego konstruktora
        reply.deserialize(reply_data);
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

bool NFS_client::is_reply_error_message(std::string &reply_data) {
    //TODO jaki format będzie po otrzymaniu danych z metody send_request
    return false;
}
