#include "server.h"

void handle_write(irc_server_t *server, int client_index)
{
    __attribute__((unused)) int clientfd = server->clientfds[client_index];

    return;
}
