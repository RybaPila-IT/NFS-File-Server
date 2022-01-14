#include <iostream>
#include <cstring>

#include "socket.h"

//temp
#include "NFS_client.h"
#include "Request.h"

#define LOOP_BACK    "127.0.0.1"
#define DEFAULT_PORT 6941

void handle_session(TcpSocket& socket) {
    int buffer_size = 1024;
    int bytes_amount;
    char buffer[buffer_size];
    std::string end_token = "END", command;
    do {
        //EXAMPLE REQUEST
        OpenRequest oReq = OpenRequest(3, "path");
        std::cout << "SIZE: "<< oReq.info.dataSize << "| TYPE: " <<oReq.info.requestType << "\n pth: "
                << oReq.filePath << " OM: " << oReq.openMode << "|SERLZ: " << oReq.Serialize() << std::endl;
        //DESERIALIZING A SUBSTRING TO SIMULATE MESSAGE AFTER SENDING (WITHOUT 4 BYTES OF SIZE AT THE FRONT)
        oReq.Deserialize(oReq.Serialize().substr(4));
        std::cout << "SIZE: "<< oReq.info.dataSize << "| TYPE: " <<oReq.info.requestType << "\n pth: "
                  << oReq.filePath << " OM: " << oReq.openMode << "|SERLZ: " << oReq.Serialize() << std::endl;



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


        //TEMP SWAPPING TYPED IN MSSG FOR CREATED REQUEST

        std::memcpy(buffer, oReq.Serialize().data(), oReq.Serialize().length() * sizeof (char ));
        std::cout << "MSG ASIGNED\n";

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