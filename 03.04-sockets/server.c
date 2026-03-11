#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    struct addrinfo hints = {0}, *addr;
    int fd, client, n;
    char buf[5];

    /* NOTE: This program (the server) will already be running, passively
     *       waiting for other programs (the clients) to connect. Thus, the
     *       server need not know the clients' addresses ahead of time. */

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    /* NOTE: Essentially, the NULL here indicates that the OS can just fill out
     *       one of our own addresses, since we're not planning to connect to
     *       someone else's address, but we do need to reserve a port. */

    getaddrinfo(NULL, argv[1], &hints, &addr);
    fd = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);

    /* NOTE: Both the client and the server will make sockets. The client will
     *       try to connect its socket to the server's, which means that server
     *       socket needs to be "bound" to a port known to the client. */

    bind(fd, addr->ai_addr, addr->ai_addrlen);
    listen(fd, 1);

    /* NOTE: If the server cares to know information about the client, such as
     *       the client's address, then it can pass pointers to structures here
     *       rather than NULLs, which will be populated with that data. */

    client = accept(fd, NULL, NULL);

    /* NOTE: Accepting a connection creates a new socket for communication with
     *       the corresponding client, thus leaving the original bound socket
     *       free to continue listening for additional clients. */

    while ((n = read(client, buf, 4)) > 0) {
        buf[n] = '\0';
        printf("Client sent \"%s\".\n", buf);
    }

    close(client);
    close(fd);
    freeaddrinfo(addr);

    return EXIT_SUCCESS;
}
