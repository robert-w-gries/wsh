#include <stdio.h>
#include "platform.h"
#include "wsh_command.h"
#include "wsh_status.h"

enum WSH_STATUS wsh_execute(wsh_command *cmd) {

	int result = my_platform.create_process(cmd);
	if (result < 0) {
		fprintf(stderr, "Application could not start\n");
		return APPLICATION_FAILURE;
	}

	return OK;

}
