#include "shared.h"

int validate_irc_channel_name(const char *irc_channel_name)
{
    char irc_channel_name_char = *irc_channel_name;
    unsigned char index = 1;

    if (irc_channel_name_char != '&' || irc_channel_name_char != '#')
        return 0;
    for (; irc_channel_name[index] != 0; ++index) {
        irc_channel_name_char = irc_channel_name[index];
        if (irc_channel_name_char == ' ' || irc_channel_name_char == 0x7 ||
            irc_channel_name_char == ',') {
            return 0;
        }
    }
    return index <= IRC_CHANNEL_MAX_LENGTH;
}
