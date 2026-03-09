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

    /* NOTE: For simplicity, we assume that we only need to handle up to 16
     *       clients, which means we need to be able to poll up to 17 file
     *       descriptors: the 16 clients and the 1 listening socket. */

    clients[0].fd = fd;
    clients[0].events = POLLIN;
    fcntl(clients[0].fd, F_SETFL, O_NONBLOCK);
    m = 1;

    while (poll(clients, m, m > 1 ? -1 : 10000) > 0) {
        /* NOTE: Since it is possible that some file descriptors are more
         *       important than others, "poll" just returns the number of file
         *       descriptors that are ready for I/O; we must search the array. */
        for (i = 0; i < m; i++) {
            if (clients[i].revents & POLLIN) {
                if (i == 0) {
                    /* NOTE: If the listening socket has data to read, use that
                     *       socket to accept a new connection and add the new
                     *       socket to the array of polled descriptors. */
                    clients[m].fd = accept(fd, NULL, NULL);
                    clients[m].events = POLLIN;
                    fcntl(clients[m].fd, F_SETFL, O_NONBLOCK);
                    m++;
                }
                else {
                    /* NOTE: If it's a client socket that has data to read,
                     *       echo all of that data to the terminal. With the
                     *       socket set to non-blocking... */
                    while ((n = read(clients[i].fd, buf, 80)) > 0) {
                        write(STDOUT_FILENO, buf, n);
                    }

                    /* NOTE: ...the above loop could break either because the
                     *       client has closed the connection or because the
                     *       client simply hasn't sent more data yet. */
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
