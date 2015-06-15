#include <stdio.h>
#include <stdlib.h>
#include "../platform/platform.h"
#include "../include/wsh_command.h"
#include "../include/wsh_status.h"
#include "../include/wsh_read.h"
#include "../include/wsh_parse.h"
#include "../include/wsh_execute.h"
#include "../include/wsh_builtin.h"

static enum WSH_STATUS wsh_loop();

int main(int argc, char **argv) {

    init_platform(&my_platform);
    init_hashtable();

    //TODO: Configurations

    enum WSH_STATUS result = wsh_loop();

    //TODO: Error reporting

    delete_hashtable();
    return result;

}

static enum WSH_STATUS wsh_loop() {

    enum WSH_STATUS status = OK;

    //my_platform.signal_handler();

    do {

        printf("> ");

        wsh_input *input = wsh_readln();
        if (input->length <= 0) {
            free(input->text);
            free(input);
            continue;
        }

        wsh_command *cmd = wsh_parseln(input);

        free(input->text);
        free(input);

        status = wsh_execute(cmd);

        cmd->delete_this(cmd);

    } while (OK == status);

    return status;

}
