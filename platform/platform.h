#ifndef _PLATFORM_H_
#define _PLATFORM_H_

#include "wsh_command.h"

struct platform_struct {
    const char *name;
    int (*change_directory)(wsh_command *);
    int (*create_process)(wsh_command *);
    void (*signal_handler)();
} typedef platform;

platform my_platform;

// general platform functions
void init_platform(platform *p);

#endif
