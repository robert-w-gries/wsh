#ifndef _WSH_BUILTIN_H_
#define _WSH_BUILTIN_H_

#include "../include/wsh_status.h"

typedef enum WSH_STATUS (*builtin_fn)(wsh_command *cmd);

void init_builtin_hashtable();
void clear_builtin_hashtable();
builtin_fn get_builtin(const char *key);

#endif
