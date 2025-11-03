#include <unistd.h>
#include <stdio.h>
#include "server.h"

int irc_deinit_server(irc_server_t *server)
{
    if (-1 == close(server->sockfd)) {
        perror("close");
        return -1;
    }
    server->sockfd = 0;

    return 0;
}
