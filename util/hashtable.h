#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include "../include/wsh_command.h"
#include "../include/wsh_status.h"

typedef enum WSH_STATUS (*builtin_fn)(wsh_command *);

struct entry_struct {
	char *key;
	enum WSH_STATUS (*value)(wsh_command *);
	struct entry_struct *next;
} typedef entry;

struct hashtable_struct {
	int size;
	entry **table;
	builtin_fn (*get)(struct hashtable_struct *, const char *);
	builtin_fn (*put)(struct hashtable_struct *, const char *, builtin_fn);
	void (*delete_this)(struct hashtable_struct *);
} typedef hashtable;

hashtable * new_hashtable(int size);
void init_hashtable(hashtable *ht);
entry ** create_table(int size);
void clear_hashtable(hashtable *ht);

#endif
