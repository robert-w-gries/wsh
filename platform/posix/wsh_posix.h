#ifndef _WSH_POSIX_H_
#define _WSH_POSIX_H_

#include "wsh_command.h"

int posix_create_process(wsh_command *cmd);
void posix_signal_handler();

#endif
