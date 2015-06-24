#ifndef _WSH_COMMAND_H_
#define _WSH_COMMAND_H_

#include "../include/wsh_command.h"

enum OUTPUT_TYPE {
    text,
    unicode,
    image,
    audio,
    video
};

struct wsh_command_struct {
    char *name;
    int nargs;
    char *args1D;
    char **args2D;
    enum OUTPUT_TYPE cmd_type;
} typedef wsh_command;

void clear_command(wsh_command *cmd);

#endif
