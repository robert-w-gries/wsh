#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "platform.h"

static void SignalHandler(int signal);

int posix_create_process(wsh_command *cmd) {

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

void posix_signal_handler() {
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
