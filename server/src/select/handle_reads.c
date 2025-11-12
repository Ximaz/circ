#include <sys/types.h>
#include "server.h"

void handle_reads(irc_server_t *server, const fd_set *reads)
{
    int client_index = server->sockfd + 1;

    for (; client_index < IRC_SERVER_MAX_CLIENTS; ++client_index) {
        if (!FD_ISSET(client_index, reads)) {
            continue;
        }
        handle_read(server, client_index);
    }
}
