#ifndef _PLATFORM_H_
#define _PLATFORM_H_

#include "../include/wsh_command.h"
#include "../include/wsh_status.h"

struct platform_struct {
    const char *name;
    enum WSH_STATUS (*change_directory)(wsh_command *);
    enum WSH_STATUS(*create_process)(wsh_command *);
    enum WSH_STATUS(*signal_handler)();
} typedef platform;

platform my_platform;

// general platform functions
void init_platform(platform *p);

#endif
