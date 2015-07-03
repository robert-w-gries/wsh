#include <dirent.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/param.h>
#include <sys/wait.h>
#include <unistd.h>
#include "platform.h"
#include "../include/wsh_status.h"

static void SignalHandler(int signal);

void init_platform(platform *p) {

    p->name = "Posix";

    p->cwd = (char *)malloc(MAXPATHLEN * sizeof(char));
    if (NULL == p->cwd) {
        fprintf(stderr, "Error: Out of memory\n");
        exit(EXIT_FAILURE);
    }

    get_current_directory();

}

enum WSH_STATUS change_directory(wsh_command *cmd) {

    char *path = cmd->args2D[1];

    // if no arguments, go to home directory
    if (1 >= cmd->nargs) {
        path = getenv("HOME");
    }

    if (0 != chdir(path)) {
        perror("wsh");
        return APPLICATION_FAILURE;
    }

    return OK;

}

enum WSH_STATUS create_process(wsh_command *cmd) {

    int status = 0;

    pid_t pid = fork();
    if (pid == 0) {
        if (execvp(cmd->args2D[0], cmd->args2D) == -1) {
            fprintf(stderr,"ERROR - %s ('%s')\n", "execvp error", cmd->args2D[0]);
            perror("wsh");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("wsh");
    } else {
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return OK;
}

char * get_current_directory() {

    int buf_size = MAXPATHLEN;
    while (NULL == getcwd(my_platform.cwd, buf_size)) {

        if (EINVAL == errno) {
            buf_size += MAXPATHLEN;
            my_platform.cwd = (char *)realloc(my_platform.cwd, buf_size * sizeof(char));
            continue;
        }

        perror("wsh");
        exit(EXIT_FAILURE);

    }

    return my_platform.cwd;

}

enum WSH_STATUS list_directory_contents(wsh_command *cmd) {

    struct dirent *dir;
    DIR *ls_dir = (1 == cmd->nargs) ? opendir(".") : opendir(cmd->args2D[1]);

    if (NULL == ls_dir) {
        perror("wsh");
        exit(EXIT_FAILURE);
    }

    while (NULL != (dir = readdir(ls_dir))) {
        printf("%s\n", dir->d_name);
    }

    closedir(ls_dir);
    return OK;

}

enum WSH_STATUS signal_handler() {
    signal(SIGINT, SignalHandler);
    signal(SIGABRT, SignalHandler);
    return OK;
}

static void SignalHandler(int signal) {

    if (SIGINT == signal) {
        printf("\n");
        exit(EXIT_FAILURE);
    } else if (SIGABRT == signal) {
        exit(EXIT_FAILURE);
    }

}
