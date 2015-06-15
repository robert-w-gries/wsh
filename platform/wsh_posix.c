#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "platform.h"
#include "../include/wsh_status.h"

static enum WSH_STATUS posix_change_directory(wsh_command *cmd);
static int posix_create_process(wsh_command *cmd);
static void posix_signal_handler();
static void SignalHandler(int signal);

void init_platform(platform *p) {

    p->name = "Posix";
    p->change_directory = &posix_change_directory;
    p->create_process = &posix_create_process;
    p->signal_handler = &posix_signal_handler;

}

static enum WSH_STATUS posix_change_directory(wsh_command *cmd) {

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

static int posix_create_process(wsh_command *cmd) {

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

    return 0;
}

static void posix_signal_handler() {
    signal(SIGINT, SignalHandler);
}

static void SignalHandler(int signal) {

    if (SIGINT == signal) {
        printf("Ctrl+C detected\n");
        exit(EXIT_FAILURE);
    } else if (SIGABRT == signal) {
        exit(EXIT_FAILURE);
    }

}
