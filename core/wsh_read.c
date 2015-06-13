#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/wsh_read.h"

#define WSH_BUF_SIZE 2048

wsh_input * wsh_readln() {

	char *line = (char *) malloc(sizeof(char) * WSH_BUF_SIZE);
    if (NULL == line) {
        fprintf(stderr, "Error: out of memory\n");
        exit(EXIT_FAILURE);
    }

	fgets(line, WSH_BUF_SIZE, stdin);

	//remove trailing newline character
	int length = strlen(line) - 1;
	if (length > 0 && line[length] == '\n') {
		line[length] = '\0';
	}

	wsh_input *input = (wsh_input *) malloc(sizeof(wsh_input));
    if (NULL == input) {
        fprintf(stderr, "Error: out of memory\n");
        exit(EXIT_FAILURE);
    }

	input->text = line;
	input->length = length;

	return input;
}
