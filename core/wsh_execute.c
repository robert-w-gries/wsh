#include <stdio.h>
#include "platform.h"
#include "wsh_command.h"
#include "wsh_status.h"
#include "wsh_builtin.h"

enum WSH_STATUS wsh_execute(wsh_command *cmd) {

    builtin_fn wsh_builtin = get_builtin(cmd->name);
    if (NULL != wsh_builtin) {
        wsh_builtin(cmd);
        return OK;
    }

    int result = my_platform.create_process(cmd);
    if (result < 0) {
        fprintf(stderr, "Application could not start\n");
        return APPLICATION_FAILURE;
    }

    return OK;

}
