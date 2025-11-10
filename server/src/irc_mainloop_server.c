#include <stdio.h>
#include <sys/select.h>
#include "server.h"

void copy_clientfds_to_fdset(const irc_server_t *server, fd_set *output)
{
    size_t fd_index = 0;

    for (; fd_index < IRC_SERVER_MAX_CLIENTS; ++fd_index) {
        if (3 < server->clientfds[fd_index]) {
            FD_ISSET(server->clientfds[fd_index], output);
        }
    }
}

static int select_file_descriptors(const irc_server_t *server,
                                   fd_set fd_sets[3])
{
    int ready_fds = -1;
    struct timeval timeout = {0, 0};

    copy_clientfds_to_fdset(server, &(fd_sets[0])); /* The reading set */
    copy_clientfds_to_fdset(server, &(fd_sets[1])); /* The writing set */
    copy_clientfds_to_fdset(server, &(fd_sets[2])); /* The exception set
                                                     */
    FD_SET(server->sockfd, &(fd_sets[0]));
    ready_fds = select(server->sockfd + 1, &(fd_sets[0]), &(fd_sets[1]),
                       &(fd_sets[2]), &timeout);
    if (-1 == ready_fds) {
        perror("select");
        return -1;
    }
    return ready_fds;
}

static int handle_fds(__attribute__((unused)) irc_server_t *server,
                      __attribute__((unused)) fd_set fd_sets[3], int ready_fds)
{
    printf("%d fds are ready to be handled.\n", ready_fds);
    return 0;
}

int irc_mainloop_server(irc_server_t *server)
{
    fd_set fd_sets[3] = {0};

    int ready_fds = select_file_descriptors(server, fd_sets);

    if (ready_fds < 1) {
        /* printf("select() output: %d\n", ready_fds); */
        return ready_fds;
    }
    return handle_fds(server, fd_sets, ready_fds);
}
