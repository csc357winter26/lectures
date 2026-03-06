#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    struct addrinfo hints = {0}, *addr;
    struct pollfd clients[17];
    int fd, n, m, i;
    char buf[80];

    /* NOTE: This program (the server) will already be running, passively
     *       waiting for other programs (the clients) to connect. Thus, the
     *       server need not know the clients' addresses ahead of time. */

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    getaddrinfo(NULL, argv[1], &hints, &addr);
    fd = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
    bind(fd, addr->ai_addr, addr->ai_addrlen);
    listen(fd, 16);

    /* NOTE: For simplicity, we'll assume that we only need to handle 16
     *       clients, which requires 17 descriptors: the 16 clients and the
     *       1 original listening socket. */

    clients[0].fd = fd;
    clients[0].events = POLLIN;
    fcntl(clients[0].fd, F_SETFL, O_NONBLOCK);
    m = 1;

    while (poll(clients, m, m > 1 ? -1 : 10000) > 0) {
        /* NOTE: Since it is generally possible that some file descriptors are
         *       more important than others, "poll" only tells us how many are
         *       ready for I/O, rather than which ones are ready for I/O. */
        for (i = 0; i < m; i++) {
            if (clients[i].revents & POLLIN) {
                if (i == 0) {

                    /* NOTE: If the listening socket has data available, we'll
                     *       accept a new client and add that client's socket
                     *       to the array of polled descriptors. */
                    clients[m].fd = accept(fd, NULL, NULL);
                    clients[m].events = POLLIN;
                    fcntl(clients[m].fd, F_SETFL, O_NONBLOCK);
                    m++;
                }
                else {

                    /* NOTE: If a client socket has data availabe, we'll read
                     *       that data and echo it to the terminal. With the
                     *       client socket set to non-blocking... */

                    while ((n = read(clients[i].fd, buf, 80)) > 0) {
                        write(STDOUT_FILENO, buf, n);
                    }

                    /* NOTE: ...there are two ways to break the above loop:
                     *       the client has closed the connection or there is
                     *       no more data available yet. */

                    if (n == 0 || errno != EAGAIN) {
                        close(clients[i].fd);
                        clients[i] = clients[m - 1];
                        m--;
                    }
                }
            }
        }
    }

    close(fd);
    freeaddrinfo(addr);

    return EXIT_SUCCESS;
}
