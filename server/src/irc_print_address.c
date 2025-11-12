#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

static void print_address_v4(const struct sockaddr *address,
                             const socklen_t *addrlen)
{
    struct sockaddr_in address_ipv4;
    struct in_addr generic_address;
    in_port_t port = 0;
    const char *hostname = NULL;

    memcpy(&address_ipv4, address, *addrlen);
    memcpy(&generic_address, &address_ipv4.sin_addr, sizeof(struct in_addr));
    hostname = inet_ntoa(address_ipv4.sin_addr);
    if (NULL == hostname) {
        perror("inet_ntoa");
        return;
    }
    port = ntohs(address_ipv4.sin_port);
    printf("New client: %s:%u (IPV4)\n", hostname, port);
}

static void print_address_v6(const struct sockaddr *address,
                             const socklen_t *addrlen)
{
    struct sockaddr_in6 address_ipv6;
    struct in_addr generic_address;
    in_port_t port = 0;
    const char *hostname = NULL;

    memcpy(&address_ipv6, address, *addrlen);
    memcpy(&generic_address, &address_ipv6.sin6_addr, sizeof(struct in_addr));
    hostname = inet_ntoa(generic_address);
    if (NULL == hostname) {
        perror("inet_ntoa");
        return;
    }
    port = ntohs(address_ipv6.sin6_port);
    printf("New client: %s:%u (IPV6)\n", hostname, port);
}

void print_address(const struct sockaddr *address, const socklen_t *addrlen)
{
    if (AF_INET == address->sa_family) {
        print_address_v4(address, addrlen);
    } else if (AF_INET6 == address->sa_family) {
        print_address_v6(address, addrlen);
    } else {
        printf("Unknown client IP protocol. (addrlen: %u)\n", *addrlen);
    }
}
