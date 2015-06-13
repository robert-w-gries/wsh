#ifndef _PLATFORM_H_
#define _PLATFORM_H_

#include "wsh_command.h"

struct platform_struct {
	const char *name;
	int (*create_process)(wsh_command *cmd);
	void (*signal_handler)();
} typedef platform;

platform my_platform;

void init_platform(platform *p);

#endif
