#include <stdio.h>
#include <stdlib.h>
#include "hashtable.h"

static int hash(hashtable *ht, Hashtable_Data key);
static Hashtable_Data get(hashtable *ht, Hashtable_Data key);
static Hashtable_Data put(hashtable *ht, Hashtable_Data key, Hashtable_Data value);
static int contains(hashtable *ht, Hashtable_Data key);
static void delete(hashtable *ht);

hashtable * new_hashtable(int size, Hashtable_Data_type type) {

	hashtable *ht = (hashtable *)malloc(sizeof(hashtable));
	if (NULL == ht) {
		fprintf(stderr, "Out of memory\n");
		exit(EXIT_FAILURE);
	}

	ht->data_type = type;
	ht->size = size;
	ht->get = &get;
	ht->put = &put;
	ht->contains = &contains;
	ht->delete = &delete;

	entry **table = (entry **)malloc(size*sizeof(entry *));
	if (NULL == table) {
		fprintf(stderr, "Out of memory\n");
		exit(EXIT_FAILURE);
	}

	ht->table = table;

	return ht;
}

static int hash(hashtable *ht, Hashtable_Data key) {

	int hashval = 0;
	int i = 0;

	switch (ht->data_type) {

		case t_voidptr: {

			for (i = 0; i < strlen(key); i++) {
				hashval = hashval << 8;
				hashval += key[i];
			}

			break;

		}

		case t_int:
		case t_char:
		case t_double:
		case t_long: {

			hashval = key;

			break;
		}

	}

	return hashval % ht->size;
}

static Hashtable_Data get(hashtable *ht, Hashtable_Data key) {

	return NULL;

}

static Hashtable_Data put(hashtable *ht, Hashtable_Data key, Hashtable_Data value) {

	entry *e = (entry *)malloc(sizeof(entry));
	e->key = key;
	e->value = value;

	return key;

}
