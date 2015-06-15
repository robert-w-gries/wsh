#ifndef _WSH_BUILTIN_H_
#define _WSH_BUILTIN_H_

#include "../util/hashtable.h"

typedef int (*builtin_fn)(wsh_command *cmd);

void init_hashtable();
void delete_hashtable();
builtin_fn get_builtin(const char *key);

#endif
