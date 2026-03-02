#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    struct addrinfo hints = {0}, *addr;

    /* NOTE: This program (the client) will actively attempt to connect to the
     *       other program (the server), which requires knowing the server's
     *       IP address and port. */

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    getaddrinfo(argv[1], argv[2], &hints, &addr);

    /* NOTE: For simplicity, we assume that the first address found by
     *       "getaddrinfo" will work rather than iterating over the linked list
     *       of potentially multiple addresses that could be tried. */

    uint32_t ipaddr = ntohl(
     ((struct sockaddr_in *)addr->ai_addr)->sin_addr.s_addr);

    printf("%d.%d.%d.%d\n",
     (ipaddr & 0xFF000000) >> 24,
     (ipaddr & 0x00FF0000) >> 16,
     (ipaddr & 0x0000FF00) >> 8,
     (ipaddr & 0x000000FF) >> 0);

    freeaddrinfo(addr);

    return EXIT_SUCCESS;
}
