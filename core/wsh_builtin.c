#include <stdio.h>
#include <stdlib.h>
#include "../platform/platform.h"
#include "../util/hashtable.h"
#include "../include/wsh_builtin.h"

static int get_num_builtins();

static enum WSH_STATUS wsh_cd(wsh_command *cmd);
static enum WSH_STATUS wsh_help(wsh_command *cmd);
static enum WSH_STATUS wsh_ls(wsh_command *cmd);
static enum WSH_STATUS wsh_exit(wsh_command *cmd);

static hashtable ht;

static const char *builtin_str[] = {
    "cd",
    "help",
    "ls",
    "exit"
};

static builtin_fn builtin_ptr[] = {
    &wsh_cd,
    &wsh_help,
    &wsh_ls,
    &wsh_exit
};

#define BUILTIN_HASHTABLE_SIZE (sizeof(builtin_str) / sizeof(const char *))

void init_builtin_hashtable() {

    if (get_num_builtins() != (sizeof(builtin_ptr) / sizeof(builtin_fn *))) {
        fprintf(stderr, "Mismatch of builtin arrays sizes\n");
        exit(EXIT_FAILURE);
    }

    init_hashtable(&ht, BUILTIN_HASHTABLE_SIZE);

    int i = 0;
    for (i = 0; i < get_num_builtins(); i++) {
        ht.put(&ht, builtin_str[i], builtin_ptr[i]);
    }

}

void clear_builtin_hashtable() {

    clear_hashtable(&ht);

} 

builtin_fn get_builtin(const char *key) {
    return ht.get(&ht, key);
}

static int get_num_builtins() {
    return sizeof(builtin_str) / sizeof(char *);
}

static enum WSH_STATUS wsh_cd(wsh_command *cmd) {

    enum WSH_STATUS result = change_directory(cmd);
    get_current_directory();
    return result;

}

static enum WSH_STATUS wsh_help(wsh_command *cmd) {

    printf("This is not helpful\n");
    return OK;

}

static enum WSH_STATUS wsh_ls(wsh_command *cmd) {

    return list_directory_contents(cmd);

}

static enum WSH_STATUS wsh_exit(wsh_command *cmd) {

    printf("Not implemented yet! Uh-oh!\n");
    return OK;

}
