#include "server.h"

void handle_exception(irc_server_t *server, int client_index)
{
    __attribute__((unused)) int clientfd = server->clientfds[client_index];

    return;
}
