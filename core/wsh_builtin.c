#include <stdio.h>
#include "../platform/platform.h"
#include "../util/hashtable.h"
#include "../include/wsh_builtin.h"

static int get_num_builtins();

static enum WSH_STATUS wsh_cd(wsh_command *cmd);
static enum WSH_STATUS wsh_help(wsh_command *cmd);
static enum WSH_STATUS wsh_exit(wsh_command *cmd);

hashtable *ht;

static const char *builtin_str[] = {
    "cd",
    "help",
    "exit"
};

static builtin_fn builtin_ptr[] = {
    &wsh_cd,
    &wsh_help,
    &wsh_exit
};

void init_hashtable() {

    ht = new_hashtable(100);

    int i = 0;
    for (i = 0; i < get_num_builtins(); i++) {
        ht->put(ht, builtin_str[i], builtin_ptr[i]);
    }

}

void delete_hashtable() {

   ht->delete_this(ht);

} 

builtin_fn get_builtin(const char *key) {
    return ht->get(ht, key);
}

static int get_num_builtins() {
    return sizeof(builtin_str) / sizeof(char *);
}

static enum WSH_STATUS wsh_cd(wsh_command *cmd) {

    return my_platform.change_directory(cmd);

}

static enum WSH_STATUS wsh_help(wsh_command *cmd) {

    printf("This is not helpful\n");
    return OK;

}

static enum WSH_STATUS wsh_exit(wsh_command *cmd) {

    printf("Not implemented yet! Uh-oh!\n");
    return OK;

}

