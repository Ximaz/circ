#include "shared.h"
#include <string.h>

/*
** We need a way to detect whether the first chunk of the raw command is a
** prefix or the actual message / command. For now, we consider there is no such
** thing as prefix, as it's easier to parse.
** TODO: take into account that prefix exist.
*/
int parse_irc_command(const char *raw_command, irc_command_t *command_output)
{
    size_t index = 0;
    /* A block can be the command or any of its parameters, it's a string. */
    size_t block_begin = 0;

    /*
    ** TODO: Count the number of total blocks, then allocate the number of
    ** blocks - 1 as a char ** for the parameters, and store the number into
    ** command_output->parameters_count.
    ** If the allocation fails, exit the function with an error status code.
    */
    while (raw_command[index] != 0) {
        while (raw_command[index] != ' ') {
            ++index;
        }

        /*
        ** Allocate a new memory block to store the command's block.
        ** length: block_begin - index + 1 (for null-terminator byte)
        ** NOTE: include a way to free the previously allocated memory blocks if
        ** the current allocation fails. Then, exit the function with error an
        ** error status, if applicable.
        */

        /*
        ** Copy the content of the command's block to the allocated memory :
        ** start: &raw_command[block_begin]
        ** end: &raw_command[index]
        */

        /*
        ** Push the current block into the irc_command_t structure. Determine
        ** whether it's a command or part of the parameters array, based on the
        ** block_begin. (If it's 0, then we surely are parsing the first block,
        ** meaning it's a command.)
        */

        while (raw_command[index] == ' ') {
            ++index;
        }
        block_begin = index;
    }
    return 0;
}
