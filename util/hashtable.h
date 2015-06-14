#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include "../include/wsh_builtin.h"

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
	void (*delete_this)(struct hashtable_struct *);
} typedef hashtable;

hashtable * new_hashtable(int size);

#endif
