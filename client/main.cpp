#include <iostream>
#include <string>
#include "socket.h"

#define LOOP_BACK    "127.0.0.1"
#define DEFAULT_PORT 6941

int main() {
    std::string data = "Half a league, half a league . . .";
    TcpSocket socket;
    try {
        socket.connect_to(LOOP_BACK, DEFAULT_PORT);
        socket.write_data(data.c_str(), data.length() * sizeof (char));
    } catch (std::runtime_error& err) {
        std::cerr << "main: " << err.what() << "\n";
        return -1;
    }
    return 0;
}

