#include <stdio.h>
#include <stdlib.h>
#include "../include/wsh_command.h"

static void delete_this(wsh_command *cmd);

wsh_command * new_wsh_command() {

    wsh_command *cmd = (wsh_command *)malloc(sizeof(wsh_command));
    if (NULL == cmd) {
        fprintf(stderr, "Error: out of memory\n");
        exit(EXIT_FAILURE);
    }

    cmd->delete_this = &delete_this;

    return cmd;

}

static void delete_this(wsh_command *cmd) {

    int i = 0;
    for (i = 0; i < cmd->nargs; i++) {

        free(cmd->args2D[i]);

    }

    free(cmd->args1D);
    free(cmd->args2D);
    free(cmd);

}

void clear_command(wsh_command *cmd) {

    free(cmd->args1D);
    free(cmd->args2D);

}

