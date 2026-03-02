#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    struct addrinfo hints = {0}, *addr;

    /* NOTE: This program (the server) will already be running, passively
     *       waiting for other programs (the clients) to connect. Thus, the
     *       server need not know the clients' addresses ahead of time. */

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    getaddrinfo(NULL, argv[1], &hints, &addr);

    freeaddrinfo(addr);

    return EXIT_SUCCESS;
}
