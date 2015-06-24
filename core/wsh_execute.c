#include <stdio.h>
#include "platform.h"
#include "wsh_command.h"
#include "wsh_status.h"
#include "wsh_builtin.h"

enum WSH_STATUS wsh_execute(wsh_command *cmd) {

    builtin_fn wsh_builtin = get_builtin(cmd->name);
    if (NULL != wsh_builtin) {
        return wsh_builtin(cmd);
    }

    return create_process(cmd);

}
