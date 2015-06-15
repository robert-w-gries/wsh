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
    init_builtin_hashtable();

    //TODO: Configurations

    enum WSH_STATUS result = wsh_loop();

    //TODO: Error reporting

    // Clean up
    delete_hashtable();
    return result;

}

static enum WSH_STATUS wsh_loop() {

    enum WSH_STATUS status = OK;

    //my_platform.signal_handler();

    do {

        printf("> ");

        wsh_input input = wsh_readln();
        if (0 >= input.length) {
            clear_input(&input);
            continue;
        }

        wsh_command cmd = wsh_parseln(&input);
        clear_input(&input);

        status = wsh_execute(&cmd);
        clear_command(&cmd);

    } while (OK == status);

    return status;

}

