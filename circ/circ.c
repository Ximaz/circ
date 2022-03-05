
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "circ.h"

int new_irc(const char *host)
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock < 0)
        return sock;

    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(IRC_PORT);

    if (inet_pton(AF_INET, host, &serv_addr.sin_addr) <= 0)
        return -2;

    const int connection = connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (connection < 0)
        return connection;

    return sock;
}

void authenticate(int sock, const char *host, const char *server, const char *nick)
{
    char *user_command = "USER %s %s %s %s :%s\r\n";
    char user_formated_command[strlen("USER     :\r\n") + strlen(host) + strlen(server) + strlen(nick) * 3 + 1];

    sprintf(user_formated_command, user_command, nick, host, server, nick, nick);
    send(sock, user_formated_command, strlen(user_formated_command), 0);

    char *nick_command = "NICK %s\r\n";
    char nick_formated_command[strlen("NICK \r\n") + strlen(nick) + 1];

    sprintf(nick_formated_command, nick_command, nick);
    send(sock, nick_formated_command, strlen(nick_formated_command), 0);

    char *buffer = malloc(sizeof(char) * SOCKET_BUFFER);
    ssize_t bytes = 0;

    while (1)
    {
        buffer[0] = '\0';
        bytes = read(sock, buffer, SOCKET_BUFFER);
        if (bytes == 0)
            break;

        if (memmem(buffer, bytes, "PING :", strlen("PING :")))
            handle_ping(sock);

        if (buffer[bytes - 1] == '\n' &&
            buffer[bytes - 2] == '\r')
            break;
    }
    free(buffer);
}

void handle_ping(int sock)
{
    send(sock, "PONG\r\n", 7, 0);
}

void join_channel(int sock, const char *channel)
{
    char *join_command = "JOIN %s\r\n";
    char command[strlen("JOIN \r\n") + strlen(channel) + 1];

    sprintf(command, join_command, channel);
    send(sock, command, strlen(command), 0);

    char *buffer = malloc(sizeof(char) * SOCKET_BUFFER);
    ssize_t bytes = 0;

    while (1)
    {
        bytes = read(sock, buffer, SOCKET_BUFFER);
        if (bytes == 0)
            break;

        if (memmem(buffer, bytes, "PING :", strlen("PING :")))
            handle_ping(sock);

        if (buffer[bytes - 1] == '\n' &&
            buffer[bytes - 2] == '\r')
            break;
    }
    free(buffer);
}

void priv_msg(int sock, const char *nick, const char *message, char *output)
{
    char *privmsg_command = "PRIVMSG %s :%s\r\n";
    char command[strlen("PRIVMSG  :\r\n") + strlen(nick) + strlen(message) + 1];

    sprintf(command, privmsg_command, nick, message);
    printf("[PRIVMSG] : %s\n", command);

    char *buffer = malloc(sizeof(char) * SOCKET_BUFFER);
    ssize_t bytes = 0;

    unsigned char response = 0;
    while (!response)
    {
        buffer[0] = '\0';

        send(sock, command, strlen(command), 0);

        bytes = read(sock, buffer, SOCKET_BUFFER);
        if (bytes == 0)
            break;

        if (memmem(buffer, bytes, "PING :", strlen("PING :")))
            handle_ping(sock);

        if (memmem(buffer, bytes, nick, strlen(nick)))
        {
            ssize_t i;
            char c;
            ssize_t skipped = 1;
            unsigned char start_copy = 0;
            for (i = 1; i < bytes; i++)
            {
                c = buffer[i];
                if (!start_copy)
                    skipped++;

                if (c == ':' && !start_copy)
                {
                    start_copy++;
                    continue;
                }

                if (start_copy)
                    output[i - skipped] = c;

                if (c == '\r' && buffer[i + 1] == '\n')
                    break;
            }

            output[i - skipped - 1] = '\0';
            response = 1;
            break;
        }
    }
    free(buffer);
}

void disconnect(int sock)
{
    const char *quit_command = "QUIT :bye";
    send(sock, quit_command, strlen(quit_command), 0);
    close(sock);
}
