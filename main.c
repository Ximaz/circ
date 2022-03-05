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
#define NICK "Ximaz"
#define CHALLENGE "!ep2"

const char *solve(const char *challenge)
{
    printf("CHALLENGE : %s\n", challenge);
    const char *answer = "ThisIsMyAnswer";
    return answer;
}

int main()
{
    int irc_socket = new_irc(HOST);

    if (irc_socket < 0)
        return irc_socket;

    authenticate(irc_socket, HOST, SERVER, NICK);
    join_channel(irc_socket, CHANNEL);

    const char *challenge = priv_msg(irc_socket, BOT, CHALLENGE);
    const char *solution = solve(challenge);
    printf("SOLUTION : %s\n", solution);

    char answer[SOCKET_BUFFER] = { '\0' };
    strcat(answer, CHALLENGE);
    strcat(answer, " -rep ");
    strcat(answer, solution);

    const char *response = priv_msg(irc_socket, BOT, answer);
    printf("RESPONSE : %s\n", response);

    disconnect(irc_socket);
    return 0;
}
