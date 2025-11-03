#ifndef __SERVER_H_
#define __SERVER_H_

#include <sys/types.h>
#include <sys/socket.h>

#define IRC_DEFAULT_PORT 6667
#define IRC_TLS_DEFAULT_PORT 6697
#define IRC_SOCKET_BACKLOG 128

typedef struct s_irc_server {
    int sockfd;
} irc_server_t;

int irc_init_server(irc_server_t *server, const char *hostname, in_port_t port,
                    sa_family_t socket_addr_family);
int irc_deinit_server(irc_server_t *server);

#endif /* !__SERVER_H_ */
