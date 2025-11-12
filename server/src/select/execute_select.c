#include <stdio.h>
#include <sys/types.h>
#include <sys/select.h>
#include "server.h"

static void prepare_select(const irc_server_t *server, fd_set *output)
{
    size_t fd_index = 0;

    for (; fd_index < IRC_SERVER_MAX_CLIENTS; ++fd_index) {
        if (3 < server->clientfds[fd_index]) {
            FD_ISSET(server->clientfds[fd_index], output);
        }
    }
}

int execute_select(const irc_server_t *server, fd_set fd_sets[3])
{
    int ready_fds = -1;
    struct timeval timeout = {0, 0};

    prepare_select(server, &(fd_sets[0])); /* The reading set */
    prepare_select(server, &(fd_sets[1])); /* The writing set */
    prepare_select(server, &(fd_sets[2])); /* The exception set */
    FD_SET(server->sockfd, &(fd_sets[0]));
    ready_fds = select(server->sockfd + 1, &(fd_sets[0]), &(fd_sets[1]),
                       &(fd_sets[2]), &timeout);
    if (-1 == ready_fds) {
        perror("select");
        return -1;
    }
    return ready_fds;
}
