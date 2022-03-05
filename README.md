# CIRC
CIRC (C IRC) is a project aiming to implement the IRC protocol using sockets in C language. It home-made, so for now, there are many things that are not handled such as SSL connections, and so on...

# Snippet
There is a snippet you can copy to try the module, which is also written in ``main.c``. It's an example of connection to ``root-me`` IRC' server which contains some challenge to solve using programming.

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "circ/circ.h"

// Constants
#define HOST "51.210.70.121" // Host has to be hand-computed for now. irc.root-me.org
#define SERVER "root-me.org"
#define CHANNEL "#root-me_challenge"
#define BOT "Candy"

// Config
#define NICK "Ximaz"
#define CHALLENGE "!ep2"

void solve(char* challenge, char* answer)
{
    // Do something there ...
}


int main()
{
    int irc_socket = new_irc(HOST);

    if (irc_socket < 0)
        return irc_socket;

    authenticate(irc_socket, HOST, SERVER, NICK);
    join_channel(irc_socket, CHANNEL);

    char challenge[SOCKET_BUFFER];
    priv_msg(irc_socket, BOT, CHALLENGE, challenge);
    printf("CHALLENGE : %s\n", challenge);

    char answer[4096] = CHALLENGE;
    strcat(answer, " -rep NONE");
    printf("ANSWER : %s\n", answer);

    char response[SOCKET_BUFFER];
    priv_msg(irc_socket, BOT, answer, response);
    printf("RESPONSE : %s\n", response);

    disconnect(irc_socket);
    return 0;
}
```
