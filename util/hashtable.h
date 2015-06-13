#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

enum Hashtable_Data_type_enum {
	t_int,
	t_char,
	t_double,
	t_long,
	t_voidptr
} typedef Hashtable_Data_type;

union Hashtable_Data_union {
	int integer_data;
	char char_data;
	double double_data;
	long long_data;
	void *generic_data;
} typedef Hashtable_Data;

struct entry_struct {
	Hashtable_Data key;
	Hashtable_Data value;
	entry *next;
} typedef entry;

struct hashtable_struct {
	Hashtable_Data_type data_type;
	int size;
	entry **table;
	Hashtable_Data (*get)(hashtable *, Hashtable_Data);
	Hashtable_Data (*put)(hashtable *, Hashtable_Data, Hashtable_Data);
	int (*contains)(hashtable *, Hashtable_Data);
	void (*delete)(hashtable *);
} typedef hashtable;

hashtable * newHashtable(int size);
entry * newEntry(Hashtable_Data key, Hashtable_Data value);

#endif
