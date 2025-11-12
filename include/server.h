#ifndef __SERVER_H_
#define __SERVER_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>

#define IRC_DEFAULT_PORT 6667
#define IRC_TLS_DEFAULT_PORT 6697
#define IRC_SOCKET_BACKLOG 128
#define IRC_SERVER_MAX_CLIENTS 32

typedef struct s_irc_server {
    int sockfd;
    int running;
    unsigned short int clientfds[IRC_SERVER_MAX_CLIENTS];
    struct sockaddr clients_addr[IRC_SERVER_MAX_CLIENTS];
} irc_server_t;

int irc_init_server(irc_server_t *server, const char *hostname, in_port_t port,
                    sa_family_t socket_addr_family);
int irc_deinit_server(irc_server_t *server);

int irc_mainloop_server(irc_server_t *server);

int execute_select(const irc_server_t *server, fd_set fd_sets[3]);

void handle_reads(irc_server_t *server, const fd_set *reads);

void handle_writes(irc_server_t *server, const fd_set *writes);

void handle_exceptions(irc_server_t *server, const fd_set *exceptions);

void handle_accept(irc_server_t *server);

void handle_read(irc_server_t *server, int client_index);

void handle_write(irc_server_t *server, int client_index);

void handle_exception(irc_server_t *server, int client_index);

void print_address(const struct sockaddr *address, const socklen_t *addrlen);

#endif /* !__SERVER_H_ */
