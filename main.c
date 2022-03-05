#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "circ/circ.h"

// Constants
#define HOST "51.210.70.121"
#define SERVER "root-me.org"
#define CHANNEL "#root-me_challenge"
#define BOT "Candy"

// Config
#define NICK "Quatrecentquatre"
#define CHALLENGE "!ep2"

void solve(char* challenge, char* answer)
{
    printf("%s\n", challenge);
    answer[0] = 'N';
    answer[1] = '\0';
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
