#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    struct addrinfo hints = {0}, *addr;
    int fd, i;
    char buf[15] = "Hello, server!";

    /* NOTE: This program (the client) will actively attempt to connect to the
     *       other program (the server), which requires knowing the server's
     *       IP address and port. */

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    getaddrinfo(argv[1], argv[2], &hints, &addr);

    /* NOTE: For simplicity, we assume that the first address found by
     *       "getaddrinfo" will work rather than iterating over the linked list
     *       of potentially multiple addresses that could be tried. */

    fd = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
    connect(fd, addr->ai_addr, addr->ai_addrlen);

    /* NOTE: It is generally possible that the entire buffer cannot be sent out
     *       all at once. This does not necessarily mean anything has gone
     *       wrong, but it is our responsibility to try sending again. */

    i = 0;
    while (i < 14) {
        i += write(fd, buf + i, 14 - i);
    }

    close(fd);
    freeaddrinfo(addr);

    return EXIT_SUCCESS;
}
