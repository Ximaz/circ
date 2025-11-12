#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include "server.h"

static int find_client_fd_slot(const irc_server_t *server)
{
    int client_index = 0;

    for (; client_index < IRC_SERVER_MAX_CLIENTS; ++client_index) {
        if (server->clientfds[client_index] <= 3) {
            return client_index;
        }
    }
    return -1;
}

void handle_accept(irc_server_t *server)
{
    struct sockaddr client_addr = {0};
    socklen_t client_addr_len = sizeof(struct sockaddr);
    int client_index = 0;
    int clientfd = accept(server->sockfd, &client_addr, &client_addr_len);

    if (-1 == clientfd) {
        perror("accept");
        return;
    }
    print_address(&client_addr, &client_addr_len);
    client_index = find_client_fd_slot(server);
    if (-1 == client_index) {
        fprintf(stderr, "Unable to accept the client: out of slots\n");
        return;
    }
    server->clientfds[client_index] = clientfd;
    memcpy(&(server->clients_addr[client_index]), &client_addr,
           client_addr_len);
}
