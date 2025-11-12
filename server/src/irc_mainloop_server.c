#include <stdio.h>
#include <sys/select.h>
#include "server.h"

int irc_mainloop_server(irc_server_t *server)
{
    fd_set fd_sets[3] = {0};
    int ready_fds = execute_select(server, fd_sets);

    if (ready_fds < 1) {
        return ready_fds;
    }
    if (FD_ISSET(server->sockfd, &(fd_sets[0]))) {
        handle_accept(server);
    }
    handle_reads(server, &(fd_sets[0]));
    handle_writes(server, &(fd_sets[1]));
    handle_exceptions(server, &(fd_sets[2]));
    return 0;
}
