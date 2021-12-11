#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <cstring>
#include <unistd.h>

#include <iostream>
#include <string>

#define DATA "Half a league, half a league . . ."

int establish_connection(const std::string& server_ip_address, const int server_port_number) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        std::cerr << "Error when opening stream socket" << std::endl;
        exit(1);
    }
    /* Get IP from args */
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    struct hostent *hp = gethostbyname(server_ip_address.c_str());
    /* hostbyname returns struct with address of host */
    if (hp == nullptr) {
        std::cerr << "Error by hostbyname: " + server_ip_address + " is unknown" << std::endl;
        exit(2);
    }
    std::memcpy((char *) &server.sin_addr, (char *) hp->h_addr,hp->h_length);
    server.sin_port = htons(server_port_number);

    if (connect(sock, (struct sockaddr *) &server, sizeof server)== -1) {
        std::cerr << "Error when connecting stream socket" << std::endl;
        exit(1);
    }
    return sock;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Wrong number of input parameters" << std::endl;
        exit(1);
    }
    std::string server_ip_address = argv[1];
    //TODO check server_ip_address
    char *dummy;
    int server_port_number = (int) std::strtol(argv[2], &dummy, 10);

    int sock = establish_connection(server_ip_address, server_port_number);

    if (write(sock, DATA, sizeof DATA) == -1)
        std::cerr << "Error when writing on stream socket" << std::endl;

    close(sock);
    exit(0);
}

