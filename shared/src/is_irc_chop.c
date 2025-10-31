#include "shared.h"

int is_irc_chop(const char *irc_nickname)
{
    return *irc_nickname == IRC_CHOP_IDENTIFIER;
}
