#include "shared.h"

int validate_irc_nickname(const char *irc_nickname)
{
    unsigned char index = 0;

    for (; irc_nickname[index] != 0; ++index) {
        /* TODO: make sure the nickname does not inclde bad characters. */
    }
    return index <= IRC_NICKNAME_MAX_LENGTH;
}
