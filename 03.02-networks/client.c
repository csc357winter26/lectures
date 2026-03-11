#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    struct addrinfo hints = {0}, *addrs, *addr;

    /* NOTE: This program (the client) will actively attempt to connect to the
     *       other program (the server), which requires knowing the server's
     *       IP address and port. */

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    /* NOTE: Here, "AF_INET" indicates a 32-bit IPv4 address (as opposed to
     *       64-bit IPv6), and "SOCK_STREAM" indicates TCP (as opposed to UDP),
     *       which are likely the common sense options as of this writing. */

    getaddrinfo(argv[1], argv[2], &hints, &addrs);

    /* NOTE: It is generally possible that the server has multiple addresses
     *       and there are multiple ways of connecting, so "getaddrinfo" will
     *       produce a linked list of addresses that we can iterate over. */

    addr = addrs;
    while (addr != NULL) {
        uint32_t ipaddr = ntohl(
         ((struct sockaddr_in *)addr->ai_addr)->sin_addr.s_addr);

        printf("%d.%d.%d.%d\n",
         (ipaddr & 0xFF000000) >> 24,
         (ipaddr & 0x00FF0000) >> 16,
         (ipaddr & 0x0000FF00) >> 8,
         (ipaddr & 0x000000FF) >> 0);

        addr = addr->ai_next;
    }

    freeaddrinfo(addrs);

    /* NOTE: None of this actually establishes a connection, or even guarantees
     *       that an attempted connection would be successful. It simply
     *       provides the information necessary to start a connection... */

    return EXIT_SUCCESS;
}
