#include <sys/types.h>
#include "server.h"

void handle_exceptions(irc_server_t *server, const fd_set *exceptions)
{
    int client_index = server->sockfd + 1;

    for (; client_index < IRC_SERVER_MAX_CLIENTS; ++client_index) {
        if (!FD_ISSET(client_index, exceptions)) {
            continue;
        }
        handle_exception(server, client_index);
    }
}
