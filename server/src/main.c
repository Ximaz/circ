#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <signal.h>
#include "server.h"

#define SERVER_HOST "127.0.0.1"

static irc_server_t server = {0};

static void intHandler(__attribute__((unused)) int dummy)
{
    server.running = 0;
    printf("Gracefully shutting down the server...\n");
}

int main(void)
{
    signal(SIGINT, intHandler);
    if (-1 ==
        irc_init_server(&server, SERVER_HOST, IRC_DEFAULT_PORT, AF_INET)) {
        fprintf(stderr,
                "An error occured when instantiating the IRC server.\n");
        return EXIT_FAILURE;
    }
    printf(
        "Server initialized correctly. Server socket file descriptor is: %d\n",
        server.sockfd);
    while (server.running) {
        if (-1 == irc_mainloop_server(&server)) {
            server.running = 0;
        }
    }
    if (-1 == irc_deinit_server(&server)) {
        fprintf(stderr, "An error occured when closing the IRC server.\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
