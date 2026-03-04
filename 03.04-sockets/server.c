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

    /* NOTE: Here, the NULL hostname indicates that we aren't trying to connect
     *       to someone else's address, but we do need to reserve a port on our
     *       own device. */

    getaddrinfo(NULL, argv[1], &hints, &addr);

    fd = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
    bind(fd, addr->ai_addr, addr->ai_addrlen);
    listen(fd, 1);

    /* NOTE: If we cared to know information about the client we accepted, such
     *       as its address, we could pass pointers here to structures that
     *       would be populated with that data. */

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
