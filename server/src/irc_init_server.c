#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include "server.h"

static int compute_sockaddr_in(struct sockaddr *address, socklen_t *address_len,
                               const char *hostname, in_port_t port)
{
    struct sockaddr_in temp_address = {0};
    struct in_addr generic_in_addr = {0};

    if (1 != inet_aton(hostname, &generic_in_addr)) {
        perror("inet_aton");
        return -1;
    }
    *address_len = sizeof(struct sockaddr_in);
    temp_address.sin_family = AF_INET;
    temp_address.sin_port = htons(port);
    memcpy(address, &temp_address, *address_len);
    memcpy(&temp_address.sin_addr, &generic_in_addr, sizeof(struct in_addr));
    return 0;
}

static int compute_sockaddr_in6(struct sockaddr *address,
                                socklen_t *address_len, const char *hostname,
                                in_port_t port)
{
    struct sockaddr_in6 temp_address = {0};
    struct in_addr generic_in_addr = {0};

    if (1 != inet_aton(hostname, &generic_in_addr)) {
        perror("inet_aton");
        return -1;
    }
    *address_len = sizeof(struct sockaddr_in6);
    temp_address.sin6_family = AF_INET6;
    temp_address.sin6_port = htons(port);
    memcpy(address, &temp_address, *address_len);
    memcpy(&temp_address.sin6_addr, &generic_in_addr, sizeof(struct in_addr));
    return 0;
}

static int bind_socket(int sockfd, const char *hostname, in_port_t port,
                       sa_family_t socket_addr_family)
{
    struct sockaddr address = {0};
    socklen_t address_len = 0;
    int address_success =
        socket_addr_family == AF_INET6
            ? compute_sockaddr_in6(&address, &address_len, hostname, port)
            : compute_sockaddr_in(&address, &address_len, hostname, port);

    if (-1 == address_success) {
        return -1;
    }
    if (-1 == bind(sockfd, &address, address_len)) {
        perror("bind");
        return -1;
    }
    if (-1 == listen(sockfd, IRC_SOCKET_BACKLOG)) {
        if (-1 == close(sockfd)) {
            perror("close");
        }
        perror("listen");
        return -1;
    }
    return 0;
}

int irc_init_server(irc_server_t *server, const char *hostname, in_port_t port,
                    sa_family_t socket_addr_family)
{
    server->sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    if (0 == server->sockfd) {
        return -1;
    }
    if (0 != bind_socket(server->sockfd, hostname, port, socket_addr_family)) {
        server->sockfd = 0;
        return -1;
    }
    server->running = 1;
    memset(&(server->clientfds), 0, sizeof(int) * IRC_SERVER_MAX_CLIENTS);
    return 0;
}
