#include <sys/types.h>
#include "server.h"

void handle_writes(irc_server_t *server, const fd_set *writes)
{
    int client_index = server->sockfd + 1;

    for (; client_index < IRC_SERVER_MAX_CLIENTS; ++client_index) {
        if (!FD_ISSET(client_index, writes)) {
            continue;
        }
        handle_write(server, client_index);
    }
}
