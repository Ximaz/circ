#ifndef __CIRC_H_
#define __CIRC_H_

#define SOCKET_BUFFER 4096
#define IRC_PORT 6667

int new_irc(const char *host);
void authenticate(int sock, const char *host, const char *server, const char *nick);
void handle_ping(int sock);
void join_channel(int sock, const char *channel);
void priv_msg(int sock, const char *nick, const char *message, char *output);
void disconnect(int sock);

#endif
