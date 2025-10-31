#ifndef __SHARED_H_
#define __SHARED_H_

#define IRC_CHANNEL_MAX_LENGTH 200
int validate_irc_channel_name(const char *irc_channel_name);

#define IRC_NICKNAME_MAX_LENGTH 9
int validate_irc_nickname(const char *irc_nickname);

#define IRC_CHOP_IDENTIFIER '@'
/* (ie replies to the NAMES, WHO and WHOIS commands) */
int is_irc_chop(const char *irc_nickname);

/* A command may include up to 15 parameters according to RFC 1459. */
#define IRC_COMMAND_MAX_PARAMETERS 15
typedef struct s_irc_command {
    const char *prefix;
    unsigned char parameters_count;
    const char *command;
    const char **parameters;
} irc_command_t;
int parse_irc_command(const char *raw_command, irc_command_t *command_output);

/*
** TODO: make sure the enum values are set according to the RFC 1459, and
** not just incrementals.
*/
typedef enum e_irc_chop_commands {
    KICK,   /* - Eject a client from the channel */
    MODE,   /* - Change the channel's mode */
    INVITE, /* - Invite a client to an invite -only channel(mode + i) */
    TOPIC   /* - Change the channel topic in a mode +t channel */
} irc_chop_commands_t;

#endif /* !__SHARED_H_ */
