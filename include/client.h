#ifndef __CLIENT_H_
#define __CLIENT_H_

typedef struct s_irc_client {
    /* The real name of the client's host on the network */
    const char *hostname;
    /* The username of the client on the host */
    const char *username;
    /* Custom nickname (9 characters max) */
    const char *nickname;

    /* TODO: Store the IRC server in a non circular-dependency way. (socket?) */
} irc_client_t;

#endif __CLIENT_H_
