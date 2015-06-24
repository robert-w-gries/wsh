#ifndef _PLATFORM_H_
#define _PLATFORM_H_

#include "../include/wsh_command.h"
#include "../include/wsh_status.h"

struct platform_struct {
    const char *name;
    char *cwd;
} typedef platform;

platform my_platform;

// general platform functions
void init_platform(platform *p);
enum WSH_STATUS change_directory(wsh_command *cmd);
enum WSH_STATUS create_process(wsh_command *cmd);
char * get_current_directory();
enum WSH_STATUS list_directory_contents(wsh_command *cmd);
enum WSH_STATUS signal_handler();

#endif
