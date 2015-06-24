#include <stdio.h>
#include <stdlib.h>
#include "../include/wsh_command.h"

void clear_command(wsh_command *cmd) {

    free(cmd->args1D);
    free(cmd->args2D);

}
