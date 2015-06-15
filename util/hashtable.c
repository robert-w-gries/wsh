#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

static unsigned long hash(const char *key);
static entry * new_entry(const char *key, builtin_fn value);

static builtin_fn get(hashtable *ht, const char *key);
static builtin_fn put(hashtable *ht, const char *key, builtin_fn fn);
static void delete_this(hashtable *ht);

hashtable * new_hashtable(int size) {

	hashtable *ht = (hashtable *)malloc(sizeof(hashtable));
	if (NULL == ht) {
		fprintf(stderr, "Error: out of memory\n");
		exit(EXIT_FAILURE);
	}

	ht->size = size;
	ht->get = &get;
	ht->put = &put;
	ht->delete_this = &delete_this;

	entry **table = (entry **)malloc(size*sizeof(entry *));
	if (NULL == table) {
		fprintf(stderr, "Error: out of memory\n");
		exit(EXIT_FAILURE);
	}

	ht->table = table;

	return ht;
}

static entry * new_entry(const char *key, builtin_fn value) {

    entry *e = (entry *)malloc(sizeof(entry));
    if (NULL == e) {
        fprintf(stderr, "Error: out of memory\n");
        exit(EXIT_FAILURE);
    }

    // make copy of read-only string 
    int length = strlen(key)+1;
    char *key_copy = (char *)malloc(sizeof(char) * length);
    if (NULL == key_copy) {
        fprintf(stderr, "Error: out of memory\n");
        exit(EXIT_FAILURE);
    }

    strncpy(key_copy, key, length);
    key_copy[length] = '\0';

    e->key = key_copy;
    e->value = value;
    e->next = NULL;

    return e;

}

// djb2 hash function
// source: http://www.cse.yorku.ca/~oz/hash.html 
static unsigned long hash(const char * key) {

    const char *str = key;
	unsigned long hashval = 5381;

    while (str) {
        hashval = ((hashval << 5) + hashval) + *str++;
	}

	return hashval;
}

static builtin_fn get(hashtable *ht, const char * key) {

    int bin = hash(key) % ht->size;
    entry *curr = ht->table[bin];

    // search for matching key
    while (0 != strcmp(curr->key, key) && NULL != curr) {
        curr = curr->next;
    } 

    // key wasn't in linked list
    if (curr == NULL) {
        return NULL;
    }

	return curr->value;

}

static builtin_fn put(hashtable *ht, const char * key, builtin_fn value) {


    // make a new entry for hashtable and get bin location
    entry *e = new_entry(key, value);
    int bin = hash(e->key) % ht->size;

    entry *curr = ht->table[bin];

    if (NULL == curr) {
        ht->table[bin] = e;
        return e->value;
    }

    // bin is non-empty; go to end of linked list
    entry *prev = NULL;
    int found_match = strcmp(curr->key, e->key);
    while (0 != found_match && NULL != curr->next) {
        prev = curr;
        curr = curr->next;
        found_match = strcmp(curr->key, e->key);
    }

    // key already exists; replace it
    if (0 == found_match) {

        builtin_fn old_value = curr->value;
        entry *curr_next = curr->next;

        free(curr->key);
        free(curr);

        // prev is NULL when replacing first item in list
        if (NULL == prev) {
            ht->table[bin] = e;
        } else {
            prev->next = e;
            e->next = curr_next;
        }

        return old_value;

    }

    // insert key at end of list
    curr->next = e;
    return NULL;

}

static void delete_this(hashtable *ht) {

    int i = 0;
    for (i = 0; i < ht->size; i++) {

        entry *e = ht->table[i];
        entry *next = NULL;

        while (e) {
            next = e->next;
            free(e->key);
            free(e);
            e = next;
        }

    }

    free(ht->table);
    free(ht);

}
