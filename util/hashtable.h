#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include "../include/wsh_command.h"
#include "../include/wsh_status.h"

typedef enum WSH_STATUS (*builtin_fn)(wsh_command *);

struct entry_struct {
    char *key;
    builtin_fn value;
    struct entry_struct *next;
} typedef entry;

struct hashtable_struct {
    int size;
    entry **table;
    builtin_fn (*get)(struct hashtable_struct *, const char *);
    builtin_fn (*put)(struct hashtable_struct *, const char *, builtin_fn);
} typedef hashtable;

void init_hashtable(hashtable *ht, int size);
void clear_hashtable(hashtable *ht);

#endif
