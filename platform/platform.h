#ifndef _PLATFORM_H_
#define _PLATFORM_H_

#include "wsh_command.h"

struct platform_struct {
	const char *name;
	int (*create_process)(wsh_command *cmd);
	void (*signal_handler)();
} typedef platform;

platform my_platform;

// general platform functions
void init_platform(platform *p);

// platform specific functions
int windows_create_process(wsh_command *cmd);
void windows_signal_handler();
int posix_create_process(wsh_command *cmd); 
void posix_signal_handler();

#endif
