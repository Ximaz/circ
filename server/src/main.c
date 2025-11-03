#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include "server.h"

int main(void)
{
    irc_server_t server = {0};

    if (-1 ==
        irc_init_server(&server, "localhost", IRC_DEFAULT_PORT, AF_INET)) {
        fprintf(stderr,
                "An error occured when instantiating the IRC server.\n");
        return EXIT_FAILURE;
    }
    printf("Server initialized correctly.\n");
    if (-1 == irc_deinit_server(&server)) {
        fprintf(stderr, "An error occured when closing the IRC server.\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
