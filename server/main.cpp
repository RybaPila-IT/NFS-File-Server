#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <cstdlib>
#include <cstring>
#include <unistd.h>

int main() {

    int sock, length;
    struct sockaddr_in server;
    int msgsock;
    char buf[1024];
    int rval;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("opening stream socket");
        exit(1);
    }
    /* dowiaz adres do gniazda */
    /* “prawdziwy” serwer pobrał by port poprzez getservbyname() */
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = 0;
    if (bind(sock, (struct sockaddr *) &server, sizeof server) == -1) {
        perror("binding stream socket");
        exit(1);
    }
    /* wydrukuj na konsoli przydzielony port */
    length = sizeof server;
    if (getsockname(sock, (struct sockaddr *) &server, reinterpret_cast<socklen_t *>(&length)) == -1) {
        perror("getting socket name");
        exit(2);
    }
    printf("Socket port #%d\n", ntohs(server.sin_port));
    /* zacznij przyjmować polaczenia... */
    listen(sock, 5);
    do{
        msgsock = accept(sock, (struct sockaddr *) 0, reinterpret_cast<socklen_t *>((int *) 0));
        if (msgsock == -1 ) {
            perror("accept");
            exit(3);
        }
        else do {
            memset(buf, 0, sizeof buf);
            if ((rval = read(msgsock,buf, 1024)) == -1) {
                perror("reading stream message");
                exit(4);
            }
            if (rval == 0)
                printf("Ending connection\n");
            else
                printf("-->%s\n", buf);
        } while (rval > 0);
        close(msgsock);
    } while(true);
/*
* gniazdo sock nie zostanie nigdy zamkniete jawnie,
* jednak wszystkie deskryptory zostana zamkniete gdy proces
* zostanie zakonczony (np w wyniku wystapienia sygnalu)
*/
}