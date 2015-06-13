#ifndef _WSH_WINDOWS_H_
#define _WSH_WINDOWS_H_

#include "wsh_command.h"

int windows_create_process(wsh_command *cmd);
void windows_signal_handler();

#endif
